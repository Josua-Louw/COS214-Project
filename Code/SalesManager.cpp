#include "SalesManager.h"
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
void SalesManager::receiveCommand(Command* command) {
    if (taskList.empty() && dynamic_cast<SellCommand*>(command)) {
        taskList.push_back(command); // Store command
        command->execute(); // Execute SellCommand
        nextStaff = nullptr; // Remove from chain (FR6)
        if (nurseryHub) {
            nurseryHub->notify(this, "SALE_COMPLETED", "Order processed"); // Notify Mediator (FR7)
        }
    } else if (nextStaff) {
        nextStaff->receiveCommand(command); // Delegate to next staff
    }
}

/**
 * @brief Handles a command request, checking availability and command type.
 * @param command Pointer to the Command to handle.
 * @return True if the command is handled, false if delegated or ignored.
 *
 * Implements the Chain of Responsibility Pattern (FR6) by checking if the SalesManager is available (taskList empty) and if the command is a SellCommand. If so, it processes the command; otherwise, it delegates to the next staff member.
 */
bool SalesManager::handleRequest(Command* command) {
    if (taskList.empty() && dynamic_cast<SellCommand*>(command)) {
        receiveCommand(command);
        return true;
    } else if (nextStaff) {
        return nextStaff->handleRequest(command);
    }
    return false;
}