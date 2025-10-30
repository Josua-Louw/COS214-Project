// TestingMain.cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

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
#include "NurseryHub.h"
#include "CareStrategy.h"
#include "RegularCareStrategy.h"
#include "SeedState.h"
#include "Plant.h"
#include "PlantImplementor.h"
#include "OrderBuilder.h"

// Optional timing shim — comment out if you didn't add Timing.h

// --- test-local stub to avoid GreenHousePlant side effects ---
class DummyImpl final : public PlantImplementor {
    std::string name_;
    double price_;
    PLANT_TYPE type_;
public:
    DummyImpl(std::string n, double p, PLANT_TYPE t)
        : name_(std::move(n)), price_(p), type_(t) {}
    PlantImplementor* clone() override { return new DummyImpl(*this); }
    double getPrice() const override { return price_; }
    std::string getName() const override { return name_; }
    PLANT_TYPE getType() const override { return type_; }
};

//minimal test OrderBuilder that filters by a target PLANT_TYPE
class TypeFilterBuilder : public OrderBuilder {
    PLANT_TYPE target_;
public:
    explicit TypeFilterBuilder(PLANT_TYPE t) : OrderBuilder(nullptr), target_(t) {}
    // Not used in these tests
    Order* buildPart(Order* order, std::string) override { return order; }
    bool checkType(Item* item) override {
        return item && item->getType() == target_;
    }
};

TEST_CASE("getPlantNamesByType with builder: only matching GREENHOUSE_PLANT names returned") {
    auto* hub = new NurseryHub();

    Plant* p1  = new Plant(new DummyImpl("aloe",   10.0, PLANT_TYPE::GREENHOUSE_PLANT));
    Plant* p2  = new Plant(new DummyImpl("bonsai", 25.0, PLANT_TYPE::GREENHOUSE_PLANT));
    Plant* p3  = new Plant(new DummyImpl("cactus", 15.5, PLANT_TYPE::GREENHOUSE_PLANT));
    Plant* pot = new Plant(new DummyImpl("clay pot", 40.0, PLANT_TYPE::POT));

    hub->registerPlant(p1);
    hub->registerPlant(p2);
    hub->registerPlant(p3);
    hub->registerPlant(pot);

    TypeFilterBuilder greenhouseBuilder(PLANT_TYPE::GREENHOUSE_PLANT);
    auto names = hub->getPlantNamesByType(&greenhouseBuilder);

    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 3);
    CHECK(names[0] == "aloe");
    CHECK(names[1] == "bonsai");
    CHECK(names[2] == "cactus");

    //sanity: pot-only filter should return just the pot
    TypeFilterBuilder potBuilder(PLANT_TYPE::POT);
    auto pots = hub->getPlantNamesByType(&potBuilder);
    REQUIRE(pots.size() == 1);
    CHECK(pots[0] == "clay pot");

    delete p1; delete p2; delete p3; delete pot;
    delete hub;
}

TEST_CASE("getPlantNamesByType with builder: empty hub returns empty") {
    auto* hub = new NurseryHub();
    TypeFilterBuilder greenhouseBuilder(PLANT_TYPE::GREENHOUSE_PLANT);
    auto names = hub->getPlantNamesByType(&greenhouseBuilder);
    CHECK(names.empty());
    delete hub;
}

TEST_CASE("getPlantNamesByType with builder: mixed types filter correctly") {
    auto* hub = new NurseryHub();

    Plant* a    = new Plant(new DummyImpl("aloe",          10.0, PLANT_TYPE::GREENHOUSE_PLANT));
    Plant* b    = new Plant(new DummyImpl("bonsai",        25.0, PLANT_TYPE::GREENHOUSE_PLANT));
    Plant* pot  = new Plant(new DummyImpl("clay pot",      40.0, PLANT_TYPE::POT));
    Plant* deco = new Plant(new DummyImpl("fairy lights",  55.0, PLANT_TYPE::DECORATION));

    hub->registerPlant(a);
    hub->registerPlant(b);
    hub->registerPlant(pot);
    hub->registerPlant(deco);

    TypeFilterBuilder greenhouseBuilder(PLANT_TYPE::GREENHOUSE_PLANT);
    auto names = hub->getPlantNamesByType(&greenhouseBuilder);
    std::sort(names.begin(), names.end());
    REQUIRE(names.size() == 2);
    CHECK(names[0] == "aloe");
    CHECK(names[1] == "bonsai");

    TypeFilterBuilder decoBuilder(PLANT_TYPE::DECORATION);
    auto decos = hub->getPlantNamesByType(&decoBuilder);
    REQUIRE(decos.size() == 1);
    CHECK(decos[0] == "fairy lights");

    delete a; delete b; delete pot; delete deco;
    delete hub;
}


// int testingMain() {
//     NurseryMediator* hub = new NurseryHub();
//     Staff* careTaker1 = new PlantCaretaker("care1",hub);
//     Staff* careTaker2 = new PlantCaretaker("care2",hub);
//     Staff* careTaker3 = new PlantCaretaker("care3",hub);
//
//     hub->registerStaff(careTaker1);
//     hub->registerStaff(careTaker2);
//     hub->registerStaff(careTaker3);
//     CareStrategy* strat1 = new RegularCareStrategy();
//     CareStrategy* strat2 = new FertilizerBoostStrategy();
//     auto* plant1 = new GreenHousePlant("plant1", 18, hub, strat1);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     auto* plant2 = new GreenHousePlant("plant2", 18, hub, strat2);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     auto* plant3 = new GreenHousePlant("plant3", 18, hub, strat1);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     auto* plant4 = new GreenHousePlant("plant4", 18, hub, strat1);
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
//     auto* plant5 = new GreenHousePlant("plant5", 18, hub, strat2);
//
//
//
//     std::this_thread::sleep_for(std::chrono::minutes(3));
//
//     delete hub;
//     delete strat1;
//     delete strat2;
//     delete careTaker1;
//     delete careTaker2;
//     delete careTaker3;
//
//
//     delete plant1;
//     delete plant2;
//     delete plant3;
//     delete plant4;
//     delete plant5;
//
//
//
//
//     return 0;
// };
// TEST_CASE("TEST") {
//     testingMain();
// }