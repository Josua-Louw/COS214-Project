#ifndef FERTILISE_PLANT_H
#define FERTILISE_PLANT_H

#include "Command.h"
#include "Plant.h"

/**
<<<<<<<< HEAD:Code/FertilisePlant.h
 * @class FertilisePlant
 * @brief Concrete command for fertilising a plant in the Plant Nursery Simulator.
========
 * @class FertilizePlant
 * @brief Concrete command for fertilizing a plant in the Plant Nursery Simulator.
>>>>>>>> origin/developer:Code/FertilizePlant.h
 * 
 * Implements the Command Pattern to encapsulate the task of fertilising a specific plant. Assigned to PlantCaretaker via NurseryHub, it interacts with a Plant to apply fertiliser, integrating with the Strategy Pattern for care routines and State Pattern for life cycle progression.
 */
class FertilizePlant: public Command {
private:
    Plant* plant; /**< The plant to be fertilised. */
public:
    /**
<<<<<<<< HEAD:Code/FertilisePlant.h
     * @brief Constructs a FertilisePlant command for a specific plant.
     * @param plant Pointer to the Plant to be fertilised.
========
     * @brief Constructs a FertilizePlant command for a specific plant.
     * @param plant Pointer to the Plant to be fertilized.
>>>>>>>> origin/developer:Code/FertilizePlant.h
     */
    FertilizePlant(Plant* plant) : plant(plant) {}
    
    /**
     * @brief Executes the fertilisation task, updating the plant's state.
     */
    void execute() override;
};

#endif // FERTILISE_PLANT_H