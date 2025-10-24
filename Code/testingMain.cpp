#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN //Do not define this anywhere else
#include "doctest.h"
#include "FertilizePlant.h"
#include "WaterPlant.h"
#include "SellCommand.h"
#include "GreenHousePlant.h"
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
 * @brief Minimal mock for GreenHousePlant to test FertilizePlant, WaterPlant, and SellCommand.
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
    std::string getName() const { return name; } // Satisfies Item::getName

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

TEST_CASE("FertilizePlant Command Tests") {
    SUBCASE("Execute calls feed on valid GreenHousePlant") {
        MockGreenHousePlant* plant = new MockGreenHousePlant();
        FertilizePlant cmd(plant);
        cmd.execute();

        CHECK(plant->fed == true);

        delete plant;
    }

    SUBCASE("Execute with null plant does nothing") {
        FertilizePlant cmd(nullptr);
        CHECK_NOTHROW(cmd.execute());
    }
}

TEST_CASE("WaterPlant Command Tests") {
    SUBCASE("Execute calls water on valid GreenHousePlant") {
        MockGreenHousePlant* plant = new MockGreenHousePlant();
        WaterPlant cmd(plant);
        cmd.execute();

        CHECK(plant->watered == true);

        delete plant;
    }

    SUBCASE("Execute with null plant does nothing") {
        WaterPlant cmd(nullptr);
        CHECK_NOTHROW(cmd.execute());
    }
}

TEST_CASE("SellCommand Command Tests") {
    SUBCASE("Execute calls addPlant and sell on valid Plant and Order") {
        MockGreenHousePlant* plant = new MockGreenHousePlant();
        MockOrder* order = new MockOrder();
        SellCommand cmd(plant, order); // MockGreenHousePlant* is a Plant*
        cmd.execute();

        CHECK(order->plantAdded == true);
        CHECK(order->addedPlant == static_cast<Plant*>(plant));
        CHECK(plant->sell(static_cast<GreenHouse*>(plant)) == 10.0);

        delete plant;
        delete order;
    }

    SUBCASE("Execute with null plant or order does nothing") {
        MockGreenHousePlant* plant = new MockGreenHousePlant();
        MockOrder* order = new MockOrder();
        SellCommand cmd1(nullptr, order);
        SellCommand cmd2(plant, nullptr);
        SellCommand cmd3(nullptr, nullptr);

        CHECK_NOTHROW(cmd1.execute());
        CHECK_NOTHROW(cmd2.execute());
        CHECK_NOTHROW(cmd3.execute());
        CHECK(order->plantAdded == false);

        delete plant;
        delete order;
    }
}



int foo() {
    return 42; // A simple function to demonstrate testing
}

TEST_CASE("Sample Test Case") {
    CHECK(foo() == 42);
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}