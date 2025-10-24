#ifndef FERTILISE_PLANT_H
#define FERTILISE_PLANT_H

#include "Command.h"
#include "Plant.h"

/**
 * @class FertilisePlant
 * @brief Concrete command for fertilising a plant in the Plant Nursery Simulator.
 * 
 * Implements the Command Pattern to encapsulate the task of fertilising a specific plant. Assigned to PlantCaretaker via NurseryHub, it interacts with a Plant to apply fertiliser, integrating with the Strategy Pattern for care routines and State Pattern for life cycle progression.
 */
class FertilisePlant : public Command {
private:
    Plant* plant; /**< The plant to be fertilised. */
public:
    /**
     * @brief Constructs a FertilisePlant command for a specific plant.
     * @param plant Pointer to the Plant to be fertilised.
     */
    FertilisePlant(Plant* plant) : plant(plant) {}
    
    /**
     * @brief Executes the fertilisation task, updating the plant's state.
     */
    void execute() override;
};

#endif // FERTILISE_PLANT_H