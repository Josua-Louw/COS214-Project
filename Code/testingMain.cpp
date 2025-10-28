// TestingMain.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <functional>

// Core headers from your code
#include "GreenHousePlant.h"
#include "RegularCareStrategy.h"
#include "FertilizerBoostStrategy.h"
#include "WaterLimitingStrategy.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "PlantCaretaker.h"
#include "NurseryMediator.h"
#include "Command.h"

// Optional timing shim — comment out if you didn't add Timing.h
#include "Timing.h"

// -------------------------------
// Test helper: lightweight Mediator
// -------------------------------
class TestMediator final : public NurseryMediator {
public:
    // optional: record calls for assertions
    std::atomic<int> begin_calls{0};
    std::atomic<int> finish_calls{0};
    std::atomic<bool> last_success{false};

    // We won't use these for routing in this test suite.
    void notify(void*, std::string, std::string) override {}
    void assign(Command*) override {} // tests call Staff directly

    void registerPlant(Plant*) override {}
    void registerStaff(Staff*) override {}

    bool isCareBusy(const GreenHousePlant* p) const override {
        return p ? p->getBusy() : false;
    }
    bool wasLastCareSuccessful(const GreenHousePlant* p) const override {
        return p ? p->getSuccess() : false;
    }
    void beginCare(GreenHousePlant* p) override {
        ++begin_calls;
        if (p) p->markCareStarted();
    }
    void finishCare(GreenHousePlant* p, bool success) override {
        ++finish_calls;
        last_success.store(success, std::memory_order_relaxed);
        if (p) p->markCareFinished(success);
    }
};

// Small helper to wait until a predicate is true or timeout expires.
static bool wait_until(std::chrono::milliseconds timeout,
                       const std::function<bool()>& pred) {
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < timeout) {
        if (pred()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    return pred();
}
// ---------------------------------
// Global test setup (fast timers)
// ---------------------------------
TEST_CASE("Set fast timing (optional)") {
    // If you added the timing shim, speed up all sleeps for tests
    timing::SPEED = 0.05; // 20s -> 1s, 2s -> 100ms, etc.
    CHECK(timing::SPEED == doctest::Approx(0.05));
}

// ---------------------------------
// Strategy unit tests (no execution)
// ---------------------------------
TEST_CASE("RegularCareStrategy returns two valid commands") {
    GreenHousePlant plant;
    RegularCareStrategy strat;
    plant.setStrategy(&strat);

    auto cmds = plant.applyCurrentCare();
    REQUIRE(cmds.size() == 2);
    REQUIRE(cmds[0] != nullptr);
    REQUIRE(cmds[1] != nullptr);
    CHECK(cmds[0]->getType() == "WaterPlant");
    CHECK(cmds[1]->getType() == "FertilizePlant");

    // cleanup commands allocated by strategies
    for (auto* c : cmds) delete c;
}

TEST_CASE("FertilizerBoostStrategy returns water then longer fertilize") {
    GreenHousePlant plant;
    FertilizerBoostStrategy strat;
    plant.setStrategy(&strat);

    auto cmds = plant.applyCurrentCare();
    REQUIRE(cmds.size() == 2);
    REQUIRE(cmds[0] != nullptr);
    REQUIRE(cmds[1] != nullptr);
    CHECK(cmds[0]->getType() == "WaterPlant");
    CHECK(cmds[1]->getType() == "FertilizePlant");
    for (auto* c : cmds) delete c;
}

TEST_CASE("WaterLimitingStrategy returns shorter water + fertilize") {
    GreenHousePlant plant;
    WaterLimitingStrategy strat;
    plant.setStrategy(&strat);

    auto cmds = plant.applyCurrentCare();
    REQUIRE(cmds.size() == 2);
    REQUIRE(cmds[0] != nullptr);
    REQUIRE(cmds[1] != nullptr);
    CHECK(cmds[0]->getType() == "WaterPlant");
    CHECK(cmds[1]->getType() == "FertilizePlant");
    for (auto* c : cmds) delete c;
}

// -------------------------------------------------
// Command + PlantCaretaker integration (async path)
// -------------------------------------------------
TEST_CASE("PlantCaretaker executes WaterPlant and marks care success") {
    TestMediator hub;
    PlantCaretaker caretaker("pc-1", &hub);

    // We bypass NurseryHub::assign (which routes via Manager) and call staff directly.
    GreenHousePlant plant("TestPlant", 12.5);

    // Produce a command with a short duration
    Command* cmd = new WaterPlant(&plant, /*time=*/1);

    // Pre-conditions
    CHECK_FALSE(plant.getBusy());
    CHECK_FALSE(plant.getSuccess());

    caretaker.receiveCommand(cmd);

    // Should quickly mark busy
    REQUIRE(wait_until(std::chrono::milliseconds(100), [&]{ return plant.getBusy(); }));

    // And eventually finish successfully (thanks to PlantCaretaker calling finishCare(..., true))
    REQUIRE(wait_until(std::chrono::milliseconds(500), [&]{ return !plant.getBusy() && plant.getSuccess(); }));

    CHECK(hub.begin_calls.load() >= 1);
    CHECK(hub.finish_calls.load() >= 1);
    CHECK(hub.last_success.load() == true);

    // cmd is owned by us; PlantCaretaker doesn't delete it
    delete cmd;
}

TEST_CASE("PlantCaretaker executes FertilizePlant and marks care success") {
    TestMediator hub;
    PlantCaretaker caretaker("pc-2", &hub);

    GreenHousePlant plant("TestPlant2", 9.99);
    Command* cmd = new FertilizePlant(&plant, /*time=*/1);

    caretaker.receiveCommand(cmd);

    REQUIRE(wait_until(std::chrono::milliseconds(100), [&]{ return plant.getBusy(); }));
    REQUIRE(wait_until(std::chrono::milliseconds(500), [&]{ return !plant.getBusy() && plant.getSuccess(); }));

    CHECK(hub.begin_calls.load() >= 1);
    CHECK(hub.finish_calls.load() >= 1);
    CHECK(hub.last_success.load() == true);

    delete cmd;
}

// -------------------------------------------------
// Watering / Fertilizing direct (blocking calls)
// -------------------------------------------------
TEST_CASE("GreenHousePlant::watering and ::fertilizing block briefly") {
    GreenHousePlant plant("TimingPlant", 1.0);

    auto t0 = std::chrono::steady_clock::now();
    plant.watering(1);
    auto t1 = std::chrono::steady_clock::now();
    plant.fertilizing(1);
    auto t2 = std::chrono::steady_clock::now();

    // With SPEED=0.05 these should be ~50ms each; allow generous slack
    auto dt1 = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    auto dt2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

    CHECK(dt1 >= 1);   // at least some delay
    CHECK(dt2 >= 1);
}

// ---------------------------------
// Sanity: price/name/type passthrough
// ---------------------------------
TEST_CASE("GreenHousePlant basics") {
    GreenHousePlant p("Rose", 19.5);
    CHECK(p.getName() == "Rose");
    CHECK(p.getPrice() == doctest::Approx(19.5));
    CHECK(p.getType() == PLANT_TYPE::GREENHOUSE_PLANT);
}

//ADAPTER TESTS

#include "SeedPacketAdapter.h"
#include "PotAdapter.h"
#include "DecorationAdapter.h"

TEST_CASE("Adapter Pattern Test Cases") {
    SUBCASE("SeedPacketAdapter Test") {
        SeedPacketAdapter spa("Rose Seeds", 10.0);
        CHECK(spa.getPrice() == 10.0);
        CHECK(spa.getName() == "Rose Seeds");
        SeedPacketAdapter spa2(new SeedPacket(15.0, "Tulip Seeds"));
        CHECK(spa2.getPrice() == 15.0);
        CHECK(spa2.getName() == "Tulip Seeds");
        CHECK(spa2.getType() == PLANT_TYPE::SEED_PACKET);
    }
    SUBCASE("PotAdapter Test") {
        PotAdapter pa("Ceramic Pot", 15.0);
        CHECK(pa.getPrice() == 15.0);
        CHECK(pa.getName() == "Ceramic Pot");
        PotAdapter pa2(new Pot(20.0, "Plastic Pot"));
        CHECK(pa2.getPrice() == 20.0);
        CHECK(pa2.getName() == "Plastic Pot");
        CHECK(pa2.getType() == PLANT_TYPE::POT);
    }
    SUBCASE("DecorationAdapter Test") {
        DecorationAdapter da("Glitter", 5.0);
        CHECK(da.getPrice() == 5.0);
        CHECK(da.getName() == "Glitter");
        DecorationAdapter da2(new Decoration(7.5, "Ribbons"));
        CHECK(da2.getPrice() == 7.5);
        CHECK(da2.getName() == "Ribbons");
        CHECK(da2.getType() == PLANT_TYPE::DECORATION);
    }
}

//TEST BRIDGE - testing plant class and plant implementor

#include "Plant.h"

TEST_CASE("Plant and plantimplementor tests") {
    SUBCASE("Plant from original creation") {
        Plant plant("Daisy", 20);
        CHECK(plant.getName() == "Daisy");
        CHECK(plant.getPrice() == 20);
        CHECK(plant.getType() == PLANT_TYPE::GREENHOUSE_PLANT);
        plant.convertToOrderType();
        CHECK(plant.getType() == PLANT_TYPE::ORDER_PLANT);
    }
    SUBCASE("Plant with Order plant implementor") {
        Plant plant(new PlantType(20, "Daisy"));
        CHECK(plant.getName() == "Daisy");
        CHECK(plant.getPrice() == 20);
        CHECK(plant.getType() == PLANT_TYPE::ORDER_PLANT);
    }
    SUBCASE("No implementor") {
        Plant plant;
        CHECK(plant.getName() == "Unnamed Plant");
        CHECK(plant.getPrice() == 0);
        CHECK(plant.getType() == PLANT_TYPE::GREENHOUSE_PLANT);
    }
}