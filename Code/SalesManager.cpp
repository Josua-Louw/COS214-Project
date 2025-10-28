#include "SalesManager.h"

#include <stdexcept>

#include "SellCommand.h"
#include "NurseryMediator.h"

/**
 * @file SalesManager.cpp
 * @brief Implementation of the SalesManager class.
 *
 * Handles sales tasks by processing SellCommand objects, supporting the Command Pattern (FR5). Participates in the Chain of Responsibility Pattern (FR6) by handling or delegating tasks via nextStaff. Interacts with NurseryHub (Mediator, FR7) for coordination with customers and inventory.
 */

/**
 * @brief Receives and executes a SellCommand, processing a customer order.
 * @param command Pointer to the Command (e.g., SellCommand) to execute.
 *
 * Executes the command if the SalesManager is available (taskList empty) and the command is a SellCommand, then removes itself from the chain and notifies NurseryHub. If busy or the command is not a SellCommand, delegates to the next staff member. Supports FR5 (Command) and FR6 (Chain of Responsibility).
 */
void SalesManager::receiveCommand(Command * command) {
    if (!staffBusy) {
        if (command == nullptr)
            throw std::invalid_argument("Command cannot be null");

        if (command->getType() != "SellCommand") {
            if (nextStaff) nextStaff->receiveCommand(command);
            return;
        }

        if (command->getAbortStatus()) {
            // nurseryHub->finishCare(command->getPlant(), false);
            return;
        }

            staffBusy = true;
            // nurseryHub->beginCare(command->getPlant());
            // command->execute();
            // nurseryHub->finishCare(command->getPlant(), true);
            staffBusy = false;
    } else {
        if (nextStaff)
            nextStaff->receiveCommand(command);
    }
}