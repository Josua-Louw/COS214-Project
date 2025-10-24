#ifndef FERTILISE_PLANT_H
#define FERTILISE_PLANT_H

#include "Command.h"
#include "Plant.h"

/**
 * @class FertilizePlant
 * @brief Concrete command for fertilizing a plant in the Plant Nursery Simulator.
 * 
 * Implements the Command Pattern to encapsulate the task of fertilizing a specific plant. Assigned to PlantCaretaker via NurseryHub, it interacts with a Plant to apply fertilizer, integrating with the Strategy Pattern for care routines and State Pattern for life cycle progression.
 */
class FertilizePlant: public Command {
private:
    Plant* plant; /**< The plant to be fertilized. */
public:
    /**
     * @brief Constructs a FertilizePlant command for a specific plant.
     * @param plant Pointer to the Plant to be fertilized.
     */
    FertilizePlant(Plant* plant) : plant(plant) {}
    
    /**
     * @brief Executes the fertilization task, updating the plant's state.
     */
    void execute() override;
};

#endif // FERTILISE_PLANT_H