#include "FertilisePlant.h"
#include "Plant.h"
#include "CareStrategy.h"
#include "PlantState.h"

/**
 * @file FertilisePlant.cpp
 * @brief Implementation of the FertilisePlant command class.
 * 
 * Executes the fertilization task for a specific plant, integrating with the Strategy Pattern (CareStrategy) and State Pattern (PlantState) to update the plant's state. Assigned to PlantCaretaker via NurseryHub (Mediator).
 */

/**
 * @brief Executes the fertilization task, updating the plant's state.
 * 
 * Calls the plant's feed method, which applies the fertilization strategy and triggers state transitions if needed. Supports FR3 (Strategy) and FR4 (State) by ensuring fertilization aligns with the plant's care requirements.
 */
void FertilisePlant::execute() {
    if (plant) {
        plant->feed(); // Calls Plant's feed method, which uses CareStrategy and updates PlantState
    }
}