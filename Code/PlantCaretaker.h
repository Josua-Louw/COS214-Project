#ifndef PLANT_CARETAKER_H
#define PLANT_CARETAKER_H

#include "Staff.h"
#include "Command.h"
<<<<<<< HEAD
#include "NurseryHub.h"
=======
>>>>>>> origin/developer
#include <string>

/**
 * @class PlantCaretaker
 * @brief Concrete staff class for managing plant care in the Plant Nursery Simulator.
 * 
 * Inherits from Staff to handle plant care tasks, implementing the Command Pattern (FR5) via receiveCommand to process commands like WaterPlant and FertilizePlant. Participates in the Chain of Responsibility Pattern (FR6) by receiving delegated tasks via nextStaff. Interacts with Plant and NurseryHub (Mediator, FR7) to update plant states.
 */
class PlantCaretaker : public Staff {
private:
    NurseryHub* nurseryHub; /**< Mediator for notifications (FR7). */
public:
    /**
     * @brief Constructs a PlantCaretaker with an ID and NurseryHub.
     * @param id Unique identifier for the PlantCaretaker.
     * @param hub Pointer to the NurseryHub mediator.
     */
    PlantCaretaker(const std::string& id, NurseryHub* hub) : Staff(id), nurseryHub(hub) {}
    
    /**
     * @brief Receives and executes a care command (e.g., WaterPlant, FertilizePlant).
     * @param command Pointer to the Command to execute.
     */
    void receiveCommand(Command* command) override;
    
    /**
     * @brief Handles a command request, checking availability and command type.
     * @param command Pointer to the Command to handle.
     * @return True if the command is handled, false if delegated or ignored.
     */
    bool handleRequest(Command* command) override;
};

#endif // PLANT_CARETAKER_H