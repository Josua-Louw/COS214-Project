#ifndef PLANT_CARETAKER_H
#define PLANT_CARETAKER_H

#include "Staff.h"
#include "Command.h"
#include "NurseryMediator.h"

#include <string>
#include <thread>
#include <mutex>
#include <memory>

using CommandPtr = std::shared_ptr<Command>;

/**
 * @class PlantCaretaker
 * @brief Concrete staff class for managing plant care in the Plant Nursery Simulator.
 *
 * Inherits from Staff to handle plant care tasks, implementing the Command Pattern (FR5) via receiveCommand to process commands like WaterPlant and FertilizePlant. Participates in the Chain of Responsibility Pattern (FR6) by receiving delegated tasks via nextStaff. Interacts with Plant and NurseryHub (Mediator, FR7) to update plant states.
 */
class PlantCaretaker : public Staff {
private:
    NurseryMediator* nurseryHub; /**< Mediator for notifications (FR7). */
    std::mutex staffMutex;
public:
    /**
     * @brief Constructs a PlantCaretaker with an ID and NurseryHub.
     * @param id Unique identifier for the PlantCaretaker.
     * @param hub Pointer to the NurseryHub mediator.
     */
    PlantCaretaker(const std::string& id, NurseryMediator* hub) : Staff(id), nurseryHub(hub) {}

    /**
     * @brief Receives and executes a care command (e.g., WaterPlant, FertilizePlant).
     * @param command Pointer to the Command to execute.
     */
    void receiveCommand(CommandPtr command) override;
    void printChain() override;

    void markFree();
};

#endif // PLANT_CARETAKER_H