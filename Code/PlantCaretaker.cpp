#include "PlantCaretaker.h"

#include <stdexcept>

#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "NurseryMediator.h"
#include <iostream>
/**
 * @file PlantCaretaker.cpp
 * @brief Implementation of the PlantCaretaker class.
 *
 * Handles plant care tasks by processing WaterPlant and FertilizePlant commands, supporting the Command Pattern (FR5). Participates in the Chain of Responsibility Pattern (FR6) by handling or delegating tasks via nextStaff. Interacts with Plant (FR3 Strategy, FR4 State) and NurseryHub (Mediator, FR7).
 */
using CommandPtr = std::shared_ptr<Command>;


void PlantCaretaker::receiveCommand(CommandPtr command) {
    std::unique_lock<std::mutex> lock(staffMutex);

    if (!command || !command->getPlant()) {
        throw std::invalid_argument("Command or Plant cannot be null");
    }

    if (!command->getPlant()->getIsAlive()) {
        return;
    }

    if (staffBusy) {
        if (nextStaff)
            nextStaff->receiveCommand(command);
        return;
    }

    if (command->getType() == "SellCommand") {
        if (nextStaff) nextStaff->receiveCommand(command);
        return;
    }

    if (command->getAbortStatus()) {
        nurseryHub->finishCare(command->getPlant(), false);
        std::cout << "Abort " << command->getPlant()->getName() << std::endl;
        return;
    }

    staffBusy = true;
    lock.unlock();

    std::thread([this, command]() {
        auto plant = command->getPlant();
        if (!plant || !plant->getIsAlive()) return;
        nurseryHub->beginCare(plant);

        if (!plant->getIsAlive()) return;

        command->execute();
        nurseryHub->finishCare(plant, true);

        {
            std::lock_guard<std::mutex> lock(staffMutex);
            staffBusy = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }).detach();
}
