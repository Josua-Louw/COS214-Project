#include "WaterPlant.h"

/**
 * @file WaterPlant.cpp
 * @brief Implementation of the WaterPlant command class.
 * 
 * Executes the watering task for a specific plant, integrating with the Strategy Pattern (CareStrategy) and State Pattern (PlantState) to update the plant's state. Assigned to PlantCaretaker via NurseryHub (Mediator).
 */

/**
 * @brief Executes the watering task, updating the plant's state.
 * 
 * Calls the plant's water method, which applies the appropriate care strategy and triggers state transitions if needed. Supports FR3 (Strategy) and FR4 (State) by ensuring watering aligns with the plant's care requirements.
 */
void WaterPlant::execute() {
    if (plant) {
        plant->watering(time); // Calls Plant's water method, which uses CareStrategy and updates PlantState
    }
}