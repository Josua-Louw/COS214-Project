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
    std::cout << "Test1" << std::endl;
    NurseryMediator* hub = new NurseryHub();
    Staff* careTaker = new PlantCaretaker("care1",hub);
    hub->registerStaff(careTaker);
    CareStrategy* strat = new RegularCareStrategy();
    auto* plant = new GreenHousePlant("plant1", 18, hub, strat);

    std::this_thread::sleep_for(std::chrono::seconds(60));

    delete hub;
    delete strat;
    delete careTaker;
    delete plant;



    return 0;
};
TEST_CASE("TEST") {
    testingMain();
}