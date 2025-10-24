#ifndef FERTILIZE_PLANT_H
#define FERTILIZE_PLANT_H

#include "Command.h"
#include "GreenHousePlant.h"

/**
 * @class FertilizePlant
 * @brief Concrete command for fertilizing a plant in the Plant Nursery Simulator.
 * 
 * Implements the Command Pattern (FR5) to encapsulate the task of fertilizing a specific greenhouse plant. Assigned to PlantCaretaker via NurseryHub (FR7), it calls GreenHousePlant’s feed method, which uses CareStrategy (FR3) and updates PlantState (FR4).
 */
class FertilizePlant : public Command {
private:
    GreenHousePlant* plant; /**< The greenhouse plant to be fertilized. */
public:
    /**
     * @brief Constructs a FertilizePlant command for a specific greenhouse plant.
     * @param plant Pointer to the GreenHousePlant to be fertilized.
     */
    FertilizePlant(GreenHousePlant* plant) : plant(plant) {}
    
    /**
     * @brief Executes the fertilization task.
     */
    void execute() override;
};

#endif // FERTILIZE_PLANT_H