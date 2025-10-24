#include "PlantCaretaker.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "NurseryHub.h"

/**
 * @file PlantCaretaker.cpp
 * @brief Implementation of the PlantCaretaker class.
 * 
 * Handles plant care tasks by processing WaterPlant and FertilizePlant commands, supporting the Command Pattern (FR5). Participates in the Chain of Responsibility Pattern (FR6) by handling or delegating tasks via nextStaff. Interacts with Plant (FR3 Strategy, FR4 State) and NurseryHub (Mediator, FR7).
 */

/**
 * @brief Receives and executes a care command (e.g., WaterPlant, FertilizePlant).
 * @param command Pointer to the Command to execute.
 * 
 * Executes the command if the PlantCaretaker is available (taskList empty) and the command is a WaterPlant or FertilizePlant command, then removes itself from the chain and notifies NurseryHub. If busy or the command is not relevant, delegates to the next staff member. Supports FR5 (Command) and FR6 (Chain of Responsibility).
 */
void PlantCaretaker::receiveCommand(Command* command) {
    if (taskList.empty() && (dynamic_cast<WaterPlant*>(command) || dynamic_cast<FertilizePlant*>(command))) {
        taskList.push_back(command); // Store command
        command->execute(); // Execute care command
        nextStaff = nullptr; // Remove from chain (FR6)
        if (nurseryHub) {
            nurseryHub->notify(this, "CARE_COMPLETED", "Plant cared for"); // Notify Mediator (FR7)
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
 * Implements the Chain of Responsibility Pattern (FR6) by checking if the PlantCaretaker is available (taskList empty) and if the command is a WaterPlant or FertilizePlant command. If so, it processes the command; otherwise, it delegates to the next staff member.
 */
bool PlantCaretaker::handleRequest(Command* command) {
    if (taskList.empty() && (dynamic_cast<WaterPlant*>(command) || dynamic_cast<FertilizePlant*>(command))) {
        receiveCommand(command);
        return true;
    } else if (nextStaff) {
        return nextStaff->handleRequest(command);
    }
    return false;
}