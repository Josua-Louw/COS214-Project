#include "FertilizePlant.h"
#include "GreenHousePlant.h"
#include "CareStrategy.h"
#include "PlantState.h"

/**
 * @file FertilizePlant.cpp
 * @brief Implementation of the FertilizePlant command class.
 * 
 * Executes the fertilization task for a specific greenhouse plant, calling GreenHousePlant’s feed method, which applies the fertilization strategy (FR3, Strategy Pattern) and updates the plant’s state (FR4, State Pattern). Assigned to PlantCaretaker via NurseryHub (Mediator, FR7). Supports the Command Pattern (FR5).
 */

/**
 * @brief Executes the fertilization task, updating the plant’s state.
 * 
 * Calls the plant’s feed method, which applies the fertilization strategy (e.g., FertilizerBoostStrategy) and triggers state transitions (e.g., JuvenileState::handleCare). Supports FR3 and FR4.
 */
void FertilizePlant::execute() {
    if (plant) {
        plant->fertilizing(time); // Calls GreenHousePlant’s feed method, using CareStrategy and PlantState
    }
}