#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN //Do not define this anywhere else
#include "doctest.h"

#include "GreenHousePlant.h"
#include "RegularCareStrategy.h"
#include "FertilizerBoostStrategy.h"
#include "WaterLimitingStrategy.h"


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

// ---- Strategy tests ----

TEST_CASE("RegularCare increases hydration & nutrition") {
    GreenHousePlant p;
    RegularCareStrategy s;
    p.setStrategy(&s);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 3);
    CHECK(p.getNutrition() == n0 + 2);
}

TEST_CASE("FertilizerBoost focuses on nutrition") {
    GreenHousePlant p;
    FertilizerBoostStrategy s;
    p.setStrategy(&s);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 2);
    CHECK(p.getNutrition() == n0 + 5);
}

TEST_CASE("WaterLimiting reduces watering pressure") {
    GreenHousePlant p;
    WaterLimitingStrategy s;
    p.setStrategy(&s);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 1);
    CHECK(p.getNutrition() == n0 + 2);
}

TEST_CASE("Switching strategies changes behavior at runtime") {
    GreenHousePlant p;
    RegularCareStrategy reg;
    FertilizerBoostStrategy fert;

    p.setStrategy(&reg);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 3);
    CHECK(p.getNutrition() == n0 + 2);

    p.setStrategy(&fert);
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 3 + 2); // +2 more from fert
    CHECK(p.getNutrition() == n0 + 2 + 5); // +5 more from fert
}
