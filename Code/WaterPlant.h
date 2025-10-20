#ifndef WATER_PLANT_H
#define WATER_PLANT_H

#include "Command.h"
#include "Plant.h"

/**
 * @class WaterPlant
 * @brief Concrete command for watering a plant in the Plant Nursery Simulator.
 * 
 * Implements the Command Pattern to encapsulate the task of watering a specific plant. Assigned to PlantCaretaker via NurseryHub, it interacts with a Plant object to apply watering care, supporting the Strategy Pattern for care routines and State Pattern for plant life cycle updates.
 */
class WaterPlant : public Command {
private:
    Plant* plant; /**< The plant to be watered. */
public:
    /**
     * @brief Constructs a WaterPlant command for a specific plant.
     * @param plant Pointer to the Plant to be watered.
     */
    WaterPlant(Plant* plant) : plant(plant) {}
    
    /**
     * @brief Executes the watering task, updating the plant's state.
     */
    void execute() override;
};

#endif // WATER_PLANT_H