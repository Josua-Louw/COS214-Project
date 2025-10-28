#include "Manager.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "SellCommand.h"
#include "NurseryHub.h"
#include "Timing.h"

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
    std::thread([this, command]() {
        timing::sleep_for(std::chrono::milliseconds(500));
        redistributeCommands(command);
    }).detach();
}

void Manager::redistributeCommands(Command * command) const {
    nurseryHub->assign(command);
}

