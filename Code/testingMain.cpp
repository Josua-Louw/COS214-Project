#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN //Do not define this anywhere else
#include "doctest.h"
#include "FertilizePlant.h"
#include "WaterPlant.h"
#include "SellCommand.h"
#include "PlantCaretaker.h"
#include "SalesManager.h"
#include "NurseryHub.h"
#include "GreenHousePlant.h"
#include "Plant.h"
#include "Order.h"
#include "GreenHouse.h"
#include <string>

/**
 * @file testingMain.cpp
 * @brief This file contains the main function for running tests using the doctest framework.
 * @details The DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN macro is defined to provide a main function for the test executable.
 * This file should be included in the test build of the project to enable test execution.
 * @note Ensure that the doctest library is properly linked in the test build configuration.
 */

// The main function is provided by the doctest framework when DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN is defined.
// No additional code is needed here.
// This file serves as the entry point for running all tests defined in other test files.

/**
 * @brief Minimal mock for NurseryHub to test notifications.
 */
class MockNurseryHub : public NurseryHub {
public:
    bool notified = false;
    std::string lastEvent;
    std::string lastData;

    void notify(void* sender, std::string event, std::string data) override {
        notified = true;
        lastEvent = event;
        lastData = data;
    }
    void assign(Command* cmd) override {}
    void registerPlant(Plant* p) override {}
    void registerStaff(Staff* s) override {}
};

/**
 * @brief Minimal mock for GreenHousePlant and Plant to test commands.
 */
class MockGreenHousePlant : public GreenHousePlant, public Plant {
public:
    bool fed = false;
    bool watered = false;
    double price = 10.0;
    std::string name = "Rose";

    // GreenHousePlant methods
    void feed() { fed = true; }
    void water() { watered = true; }
    double getPrice() const { return price; }
    std::string getType() const { return "MockGreenHousePlant"; }
    PlantImplementor* clone() { return new MockGreenHousePlant(*this); }
    std::string getName() const { return name; }

    // Plant methods
    void convertToOrderType() {}
    std::string getImplementorType() { return "MockGreenHousePlant"; }

    // GreenHouse methods (via Item)
    double sell(GreenHouse* item) {
        if (dynamic_cast<MockGreenHousePlant*>(item) == this) {
            return price;
        }
        return 0.0;
    }
    void expand(GreenHouse*) {}
    GreenHouse* getSubsection(std::string) { return nullptr; }
    Iterator* CreateIterator() { return nullptr; }
    Plant* findItem(std::string itemName) {
        return (itemName == name) ? this : nullptr;
    }
};

/**
 * @brief Minimal mock for Order to test SellCommand.
 */
class MockOrder : public Order {
public:
    bool plantAdded = false;
    Plant* addedPlant = nullptr;

    void addPlant(Plant* p) {
        plantAdded = true;
        addedPlant = p;
    }
};

TEST_CASE("Chain of Responsibility Tests for PlantCaretaker and SalesManager") {
    MockNurseryHub* hub = new MockNurseryHub();
    MockGreenHousePlant* plant = new MockGreenHousePlant();
    MockOrder* order = new MockOrder();

    SUBCASE("PlantCaretaker handles WaterPlant command") {
        PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
        WaterPlant* cmd = new WaterPlant(plant);

        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(plant->watered == true);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        CHECK(hub->notified == true);
        CHECK(hub->lastEvent == "CARE_COMPLETED");
        CHECK(hub->lastData == "Plant cared for");

        delete cmd;
        delete caretaker;
    }

    SUBCASE("PlantCaretaker handles FertilizePlant command") {
        PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
        FertilizePlant* cmd = new FertilizePlant(plant);

        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(plant->fed == true);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        CHECK(hub->notified == true);
        CHECK(hub->lastEvent == "CARE_COMPLETED");
        CHECK(hub->lastData == "Plant cared for");

        delete cmd;
        delete caretaker;
    }

    SUBCASE("PlantCaretaker delegates SellCommand to SalesManager") {
        PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
        SalesManager* manager = new SalesManager("SM1", hub);
        caretaker->setNextStaff(manager);
        SellCommand* cmd = new SellCommand(plant, order);

        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(caretaker->getTaskList().size() == 0);
        CHECK(caretaker->getNextStaff() == manager);
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getNextStaff() == nullptr);
        CHECK(order->plantAdded == true);
        CHECK(order->addedPlant == static_cast<Plant*>(plant));
        CHECK(hub->notified == true);
        CHECK(hub->lastEvent == "SALE_COMPLETED");
        CHECK(hub->lastData == "Order processed");

        delete cmd;
        delete manager;
        delete caretaker;
    }

    SUBCASE("SalesManager handles SellCommand") {
        SalesManager* manager = new SalesManager("SM1", hub);
        SellCommand* cmd = new SellCommand(plant, order);

        bool handled = manager->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(order->plantAdded == true);
        CHECK(order->addedPlant == static_cast<Plant*>(plant));
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getNextStaff() == nullptr);
        CHECK(hub->notified == true);
        CHECK(hub->lastEvent == "SALE_COMPLETED");
        CHECK(hub->lastData == "Order processed");

        delete cmd;
        delete manager;
    }

    SUBCASE("SalesManager delegates WaterPlant to PlantCaretaker") {
        SalesManager* manager = new SalesManager("SM1", hub);
        PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
        manager->setNextStaff(caretaker);
        WaterPlant* cmd = new WaterPlant(plant);

        bool handled = manager->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(manager->getTaskList().size() == 0);
        CHECK(manager->getNextStaff() == caretaker);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        CHECK(plant->watered == true);
        CHECK(hub->notified == true);
        CHECK(hub->lastEvent == "CARE_COMPLETED");
        CHECK(hub->lastData == "Plant cared for");

        delete cmd;
        delete caretaker;
        delete manager;
    }

    SUBCASE("No staff handles unmatched command") {
        PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
        SalesManager* manager = new SalesManager("SM1", hub);
        caretaker->setNextStaff(manager);
        class DummyCommand : public Command {
        public:
            void execute() override {}
        };
        DummyCommand* cmd = new DummyCommand();

        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == false);
        CHECK(caretaker->getTaskList().size() == 0);
        CHECK(manager->getTaskList().size() == 0);
        CHECK(caretaker->getNextStaff() == manager);
        CHECK(manager->getNextStaff() == nullptr);
        CHECK(hub->notified == false);

        delete cmd;
        delete manager;
        delete caretaker;
    }

    delete plant;
    delete order;
    delete hub;
}

int foo() {
    return 42; // A simple function to demonstrate testing
}

TEST_CASE("Sample Test Case") {
    CHECK(foo() == 42);
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}