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
#include "NurseryHub.h"
#include "CareStrategy.h"
#include "RegularCareStrategy.h"
#include "SeedState.h"
// Optional timing shim — comment out if you didn't add Timing.h


int testingMain() {
    NurseryMediator* hub = new NurseryHub();
    Staff* careTaker1 = new PlantCaretaker("care1",hub);
    Staff* careTaker2 = new PlantCaretaker("care2",hub);
    Staff* careTaker3 = new PlantCaretaker("care3",hub);

    hub->registerStaff(careTaker1);
    hub->registerStaff(careTaker2);
    hub->registerStaff(careTaker3);
    CareStrategy* strat1 = new RegularCareStrategy();
    CareStrategy* strat2 = new FertilizerBoostStrategy();
    auto* plant1 = new GreenHousePlant("plant1", 18, hub, strat1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto* plant2 = new GreenHousePlant("plant2", 18, hub, strat2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto* plant3 = new GreenHousePlant("plant3", 18, hub, strat1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto* plant4 = new GreenHousePlant("plant4", 18, hub, strat1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto* plant5 = new GreenHousePlant("plant5", 18, hub, strat2);



    std::this_thread::sleep_for(std::chrono::minutes(3));

    delete hub;
    delete strat1;
    delete strat2;
    delete careTaker1;
    delete careTaker2;
    delete careTaker3;


    delete plant1;
    delete plant2;
    delete plant3;
    delete plant4;
    delete plant5;




    return 0;
};
TEST_CASE("TEST") {
    testingMain();
}