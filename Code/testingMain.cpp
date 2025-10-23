#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN //Do not define this anywhere else
#include "doctest.h"

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

int foo() {
    return 42; // A simple function to demonstrate testing
}

TEST_CASE("Sample Test Case") {
    CHECK(foo() == 42);
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}

//TEST for seed packet functionality
#include "SeedPacket.h"

TEST_CASE("Seed Packet Test Case") {
    SUBCASE("Default Constructor") {
        SeedPacket sp;
        CHECK(sp.getPrice() == 0.0);
        CHECK(sp.getName() == "");
    }
    SUBCASE("Parameterized Constructor") {
        SeedPacket sp2(10.0, "Rose Seeds");
        CHECK(sp2.getPrice() == 10.0);
        CHECK(sp2.getName() == "Rose Seeds");
        CHECK(sp2.getType() == PLANT_TYPE::SEED_PACKET);
    }
    SUBCASE("Copy Constructor") {
        SeedPacket sp3(15.0, "Tulip Seeds");
        SeedPacket sp4(sp3);
        CHECK(sp4.getPrice() == 15.0);
        CHECK(sp4.getName() == "Tulip Seeds");
        CHECK(sp4.getType() == PLANT_TYPE::SEED_PACKET);
    }
    SUBCASE("Clone Method") {
        SeedPacket sp5(20.0, "Daisy Seeds");
        PlantImplementor* spClone = sp5.clone();
        SeedPacket* spCloneCasted = dynamic_cast<SeedPacket*>(spClone);
        REQUIRE(spCloneCasted != nullptr);
        CHECK(spCloneCasted->getPrice() == 20.0);
        CHECK(spCloneCasted->getName() == "Daisy Seeds");
        CHECK(spCloneCasted->getType() == PLANT_TYPE::SEED_PACKET);
        delete spClone; // Clean up cloned object
    }
}