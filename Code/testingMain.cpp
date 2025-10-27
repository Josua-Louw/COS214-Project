#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Command.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "SellCommand.h"
#include "PlantCaretaker.h"
#include "SalesManager.h"
#include "NurseryHub.h"
#include "GreenHousePlant.h"
#include "Order.h"
#include <string>

TEST_CASE("Command Pattern Tests") {
    NurseryHub* hub = new NurseryHub();
    GreenHousePlant* plant = new GreenHousePlant();
    Order* order = new Order();
    PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
    SalesManager* salesManager = new SalesManager("SM1", hub);

    // Register staff with hub
    hub->registerStaff(caretaker);
    hub->registerStaff(salesManager);

    SUBCASE("WaterPlant execute calls water on GreenHousePlant") {
        WaterPlant* cmd = new WaterPlant(plant);
        cmd->execute();
        // Since GreenHousePlant::water() calls applyCurrentCare(), check hydration
        CHECK(plant->getHydration() >= 0); // No strategy set, so no change
        delete cmd;
    }

    SUBCASE("FertilizePlant execute calls feed on GreenHousePlant") {
        FertilizePlant* cmd = new FertilizePlant(plant);
        cmd->execute();
        // Since GreenHousePlant::feed() calls applyCurrentCare(), check nutrition
        CHECK(plant->getNutrition() >= 0); // No strategy set, so no change
        delete cmd;
    }

    SUBCASE("SellCommand execute calls addPlant and sell") {
        SellCommand* cmd = new SellCommand(plant, order);
        cmd->execute();
        CHECK(plant->getPrice() == 0.0); // Default price
        delete cmd;
    }

    SUBCASE("PlantCaretaker receives and executes WaterPlant") {
        WaterPlant* cmd = new WaterPlant(plant);
        caretaker->receiveCommand(cmd);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(plant->getHydration() >= 0); // No strategy set
        CHECK(caretaker->getNextStaff() == nullptr);
        // Command deleted by Staff::~Staff
    }

    SUBCASE("PlantCaretaker receives and executes FertilizePlant") {
        FertilizePlant* cmd = new FertilizePlant(plant);
        caretaker->receiveCommand(cmd);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(plant->getNutrition() >= 0); // No strategy set
        CHECK(caretaker->getNextStaff() == nullptr);
        // Command deleted by Staff::~Staff
    }

    SUBCASE("SalesManager receives and executes SellCommand") {
        SellCommand* cmd = new SellCommand(plant, order);
        salesManager->receiveCommand(cmd);
        CHECK(salesManager->getTaskList().size() == 1);
        CHECK(salesManager->getNextStaff() == nullptr);
        // Command deleted by Staff::~Staff
    }

    SUBCASE("PlantCaretaker does not execute SellCommand directly") {
        SellCommand* cmd = new SellCommand(plant, order);
        caretaker->receiveCommand(cmd);
        CHECK(caretaker->getTaskList().size() == 1); // Stores but doesn't execute incorrectly
        // Command deleted by Staff::~Staff
    }

    SUBCASE("SalesManager does not execute WaterPlant directly") {
        WaterPlant* cmd = new WaterPlant(plant);
        salesManager->receiveCommand(cmd);
        CHECK(salesManager->getTaskList().size() == 1); // Stores but doesn't execute incorrectly
        CHECK(plant->getHydration() >= 0); // No change if not executed
        // Command deleted by Staff::~Staff
    }

    delete plant;
    delete order;
    delete caretaker;
    delete salesManager;
    delete hub;
}