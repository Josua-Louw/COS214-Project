#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Staff.h"
#include "PlantCaretaker.h"
#include "SalesManager.h"
#include "Manager.h"
#include "Command.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "SellCommand.h"
#include "NurseryHub.h"
#include "GreenHousePlant.h"
#include "Plant.h"
#include "Order.h"
#include <string>

TEST_CASE("Chain of Responsibility Tests") {
    NurseryHub* hub = new NurseryHub();
    GreenHousePlant* plant = new GreenHousePlant(); // Default constructor
    Order* order = new Order();
    PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
    SalesManager* salesManager = new SalesManager("SM1", hub);
    Manager* manager = new Manager("M1", hub);

    // Register staff with hub for redistribution
    hub->registerStaff(caretaker);
    hub->registerStaff(salesManager);
    hub->registerStaff(manager);

    SUBCASE("Chain setup with addStaffMemeber") {
        caretaker->addStaffMemeber(salesManager);
        salesManager->addStaffMemeber(manager);
        CHECK(caretaker->getNextStaff() == salesManager);
        CHECK(salesManager->getNextStaff() == manager);
        CHECK(manager->getNextStaff() == nullptr);
    }

    SUBCASE("Clear task lists") {
        caretaker->clearTaskList();
        salesManager->clearTaskList();
        manager->clearTaskList();
        CHECK(caretaker->getTaskList().size() == 0);
        CHECK(salesManager->getTaskList().size() == 0);
        CHECK(manager->getTaskList().size() == 0);
        CHECK(manager->getPendingCommandsSize() == 0);
    }

    SUBCASE("PlantCaretaker handles WaterPlant") {
        Command* cmd = new WaterPlant(plant);
        caretaker->addStaffMemeber(salesManager);
        salesManager->addStaffMemeber(manager);
        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        CHECK(salesManager->getTaskList().size() == 0);
        CHECK(manager->getTaskList().size() == 0);
        delete cmd;
    }

    SUBCASE("PlantCaretaker handles FertilizePlant") {
        Command* cmd = new FertilizePlant(plant);
        caretaker->addStaffMemeber(salesManager);
        salesManager->addStaffMemeber(manager);
        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        CHECK(salesManager->getTaskList().size() == 0);
        CHECK(manager->getTaskList().size() == 0);
        delete cmd;
    }

    SUBCASE("SalesManager handles SellCommand") {
        Command* cmd = new SellCommand(plant, order);
        salesManager->addStaffMemeber(manager);
        bool handled = salesManager->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(salesManager->getTaskList().size() == 1);
        CHECK(salesManager->getNextStaff() == nullptr);
        CHECK(manager->getTaskList().size() == 0);
        delete cmd;
    }

    SUBCASE("PlantCaretaker delegates SellCommand to SalesManager") {
        Command* cmd = new SellCommand(plant, order);
        caretaker->addStaffMemeber(salesManager);
        salesManager->addStaffMemeber(manager);
        bool handled = caretaker->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(caretaker->getTaskList().size() == 0);
        CHECK(caretaker->getNextStaff() == salesManager);
        CHECK(salesManager->getTaskList().size() == 1);
        CHECK(salesManager->getNextStaff() == nullptr);
        CHECK(manager->getTaskList().size() == 0);
        delete cmd;
    }

    SUBCASE("SalesManager delegates WaterPlant to PlantCaretaker") {
        Command* cmd = new WaterPlant(plant);
        salesManager->addStaffMemeber(caretaker);
        caretaker->addStaffMemeber(manager);
        bool handled = salesManager->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(salesManager->getTaskList().size() == 0);
        CHECK(salesManager->getNextStaff() == caretaker);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        CHECK(manager->getTaskList().size() == 0);
        delete cmd;
    }

    SUBCASE("Chain delegates FertilizePlant to Manager for queuing") {
        Command* cmd = new FertilizePlant(plant);
        salesManager->addStaffMemeber(manager);
        bool handled = salesManager->handleRequest(cmd);
        CHECK(handled == true);
        CHECK(salesManager->getTaskList().size() == 0);
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 1);
        delete cmd;
    }

    SUBCASE("Manager redistributes WaterPlant to PlantCaretaker") {
        Command* cmd = new WaterPlant(plant);
        caretaker->clearTaskList();
        salesManager->clearTaskList();
        manager->receiveCommand(cmd);
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 1);
        manager->redistributeCommands();
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 0);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(caretaker->getNextStaff() == nullptr);
        delete cmd;
    }

    SUBCASE("Manager redistributes SellCommand to SalesManager") {
        Command* cmd = new SellCommand(plant, order);
        caretaker->clearTaskList();
        salesManager->clearTaskList();
        manager->receiveCommand(cmd);
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 1);
        manager->redistributeCommands();
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 0);
        CHECK(salesManager->getTaskList().size() == 1);
        CHECK(salesManager->getNextStaff() == nullptr);
        delete cmd;
    }

    SUBCASE("Manager redistributes with no available staff") {
        Command* cmd = new WaterPlant(plant);
        caretaker->receiveCommand(new FertilizePlant(plant));
        salesManager->receiveCommand(new SellCommand(plant, order));
        manager->receiveCommand(cmd);
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 1);
        manager->redistributeCommands();
        CHECK(manager->getTaskList().size() == 1);
        CHECK(manager->getPendingCommandsSize() == 0);
        CHECK(caretaker->getTaskList().size() == 1);
        CHECK(salesManager->getTaskList().size() == 1);
        delete cmd;
    }

    delete plant;
    delete order;
    delete caretaker;
    delete salesManager;
    delete manager;
    delete hub;
}