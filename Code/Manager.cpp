#include "Manager.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "SellCommand.h"
#include "NurseryHub.h"

/**
 * @file Manager.cpp
 * @brief Implementation of the Manager class.
 * 
 * Handles task distribution by queuing unhandled commands (FR6) and redistributing them via NurseryHub (FR7). Supports the Command Pattern (FR5) by storing commands and the Chain of Responsibility Pattern (FR6) as the final handler in the chain.
 */

/**
 * @brief Receives and queues a command if no prior staff can handle it.
 * @param command Pointer to the Command to handle or queue.
 * 
 * Queues the command in pendingCommands and notifies NurseryHub. Supports FR5 (Command) and FR6 (Chain of Responsibility).
 */
void Manager::receiveCommand(Command* command) {
    if (command) {
        pendingCommands.push(command); // Queue command
        taskList.push_back(command); // Store in taskList for FR5
        if (nurseryHub) {
            nurseryHub->notify(this, "COMMAND_QUEUED", "Command queued by Manager");
        }
    }
}

/**
 * @brief Handles a command request by queuing it if no staff are available.
 * @param command Pointer to the Command to handle.
 * @return True if the command is queued, false if ignored.
 * 
 * Implements the Chain of Responsibility Pattern (FR6) by queuing commands when no staff are available.
 */
bool Manager::handleRequest(Command* command) {
    if (command) {
        receiveCommand(command);
        return true;
    }
    return false;
}

/**
 * @brief Redistributes pending commands to available staff via NurseryHub.
 * 
 * Attempts to assign each queued command through NurseryHub, clearing the pending queue afterward.
 */
void Manager::redistributeCommands() {
    while (!pendingCommands.empty()) {
        Command* cmd = pendingCommands.front();
        if (nurseryHub) {
            nurseryHub->assign(cmd); // Reassign via NurseryHub
            pendingCommands.pop();
            if (nurseryHub) {
                nurseryHub->notify(this, "COMMAND_REASSIGNED", "Command reassigned to staff");
            }
        } else {
            if (nurseryHub) {
                nurseryHub->notify(this, "NO_STAFF_AVAILABLE", "No staff available for reassignment");
            }
            break; // Cannot reassign without NurseryHub
        }
    }
}

