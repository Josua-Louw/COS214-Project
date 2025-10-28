#include "PlantCaretaker.h"

#include <stdexcept>

#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "NurseryMediator.h"

/**
 * @file PlantCaretaker.cpp
 * @brief Implementation of the PlantCaretaker class.
 *
 * Handles plant care tasks by processing WaterPlant and FertilizePlant commands, supporting the Command Pattern (FR5). Participates in the Chain of Responsibility Pattern (FR6) by handling or delegating tasks via nextStaff. Interacts with Plant (FR3 Strategy, FR4 State) and NurseryHub (Mediator, FR7).
 */

void PlantCaretaker::receiveCommand(Command * command) {
    if (!staffBusy) {
        if (command == nullptr)
            throw std::invalid_argument("Command cannot be null");

        if (command->getType() == "SellCommand") {
            if (nextStaff) nextStaff->receiveCommand(command);
            return;
        }

        if (command->getAbortStatus()) {
            nurseryHub->finishCare(command->getPlant(), false);
            delete command;
            return;
        }

        std::thread([this, command]() {
            staffBusy = true;
            nurseryHub->beginCare(command->getPlant());
            command->execute();
            nurseryHub->finishCare(command->getPlant(), true);
            staffBusy = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            delete command;
        }).detach();
    } else {
        if (nextStaff)
            nextStaff->receiveCommand(command);
    }
}
