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
    SUBCASE("Decorate Method") {
        SeedPacket sp6(25.0, "Sunflower Seeds");
        // Since decorate does nothing for SeedPacket, just ensure it doesn't throw
        CHECK_NOTHROW(sp6.decorate(&sp6));
        CHECK(sp6.getPrice() == 25.0); // Price should remain unchanged
    }
}

//TEST for Decorator functionality
#include "Decoration.h"

TEST_CASE("Decoration Test Case") {
    SUBCASE("Default Constructor") {
        Decoration dec;
        CHECK(dec.getPrice() == 0.0);
        CHECK(dec.getName() == "");
    }
    SUBCASE("Parameterized Constructor") {
        Decoration dec2(5.0, "Glitter");
        CHECK(dec2.getPrice() == 5.0);
        CHECK(dec2.getName() == "Glitter");
        CHECK(dec2.getType() == PLANT_TYPE::DECORATION);
    }
    SUBCASE("Copy Constructor") {
        Decoration dec3(7.5, "Ribbons");
        Decoration dec4(dec3);
        CHECK(dec4.getPrice() == 7.5);
        CHECK(dec4.getName() == "Ribbons");
        CHECK(dec4.getType() == PLANT_TYPE::DECORATION);
    }
    SUBCASE("Clone Method") {
        Decoration dec5(12.0, "Beads");
        PlantImplementor* decClone = dec5.clone();
        Decoration* decCloneCasted = dynamic_cast<Decoration*>(decClone);
        REQUIRE(decCloneCasted != nullptr);
        CHECK(decCloneCasted->getPrice() == 12.0);
        CHECK(decCloneCasted->getName() == "Beads");
        CHECK(decCloneCasted->getType() == PLANT_TYPE::DECORATION);
        delete decClone; // Clean up cloned object
    }
    SUBCASE("Decoration on SeedPacket") {
        SeedPacket* sp = new SeedPacket(10.0, "Sunflower Seeds");
        Decoration dec(3.0, "Sparkles");
        dec.decorate(sp);
        CHECK(dec.getPrice() == 13.0); // 10 + 3
        CHECK(sp->getPrice() == 10.0); // Original seed packet price remains unchanged
        CHECK(sp->getName() == "Sunflower Seeds");
        CHECK(sp->getType() == PLANT_TYPE::SEED_PACKET);
        CHECK(dec.getType() == PLANT_TYPE::DECORATION);
        CHECK(dec.getName() == "Sparkles");
        SUBCASE("Double Decoration with seeds Error") {
            SeedPacket* sp2 = new SeedPacket(2.0, "Glitter");
            CHECK_THROWS_AS(dec.decorate(sp2), const char*);
            delete sp2; // Clean up seed packet
        }
        SUBCASE("Decoration Chain") {
            Decoration* dec2 = new Decoration(2.0, "Ribbons");
            dec.decorate(dec2);
            CHECK(dec.getPrice() == 15.0); // 10 + 3 + 2
            CHECK(dec2->getName() == "Ribbons");
            CHECK(dec2->getType() == PLANT_TYPE::DECORATION);
        }
        SUBCASE("Longer decoration Chain") {
            Decoration newDec(3.0, "Flowers");
            Decoration* dec3 = new Decoration(1.0, "Beads");
            Decoration* dec4 = new Decoration(2.0, "Lights");
            newDec.decorate(dec3);
            newDec.decorate(dec4);
            CHECK(newDec.getPrice() == 6.0); // 3 + 1 + 2
        }
        SUBCASE("Null Decoration") {
            Decoration decNull(4.0, "Feathers");
            decNull.decorate(nullptr); // Should handle gracefully
            CHECK(decNull.getPrice() == 4.0); // Price remains unchanged
        }
    }
    
}