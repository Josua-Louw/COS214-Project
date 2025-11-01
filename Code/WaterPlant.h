#ifndef WATER_PLANT_H
#define WATER_PLANT_H

#include "Command.h"
#include "GreenHousePlant.h"

/**
 * @class WaterPlant
 * @brief Concrete command for watering a plant in the Plant Nursery Simulator.
 * 
 * Implements the Command Pattern to encapsulate the task of watering a specific plant. Assigned to PlantCaretaker via NurseryHub, it interacts with a Plant object to apply watering care, supporting the Strategy Pattern for care routines and State Pattern for plant life cycle updates.
 */
class WaterPlant : public Command {
private:
    GreenHousePlant* plant; /**< The plant to be watered. */
    int time;

public:
    /**
     * @brief Constructs a WaterPlant command for a specific plant.
     * @param plant Pointer to the GreenHousePlant to be watered.
     */
    WaterPlant(GreenHousePlant* plant, int time) : plant(plant), time(time){}

    std::string getType() override;

    GreenHousePlant* getPlant() override;

    /**
     * @brief Executes the watering task, updating the plant's state.
     */
    void execute() override;
};

#endif // WATER_PLANT_H