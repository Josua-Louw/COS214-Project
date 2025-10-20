#ifndef PLANT_CARETAKER_H
#define PLANT_CARETAKER_H

#include "Staff.h"

/**
 * @class PlantCaretaker
 * @brief Concrete staff class for managing plant care in the Plant Nursery Simulator.
 * 
 * Inherits from Staff to handle plant care tasks, implementing the Command Pattern via receiveCommand to process commands like WaterPlant and FertilisePlant. Participates in the Chain of Responsibility Pattern by receiving delegated tasks via nextStaff. Interacts with Plant and NurseryHub (Mediator) to update plant states.
 */
class PlantCaretaker : public Staff {
public:
    /**
     * @brief Constructs a PlantCaretaker with an ID.
     * @param id Unique identifier for the PlantCaretaker.
     */
    PlantCaretaker(const std::string& id) : Staff(id) {}
    
    /**
     * @brief Receives and executes a care command (e.g., WaterPlant, FertilisePlant).
     * @param command Pointer to the Command to execute.
     */
    void receiveCommand(Command* command) override;
};

#endif // PLANT_CARETAKER_H