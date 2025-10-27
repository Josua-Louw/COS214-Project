#ifndef MANAGER_H
#define MANAGER_H   

#include "Staff.h"
#include "Command.h"
#include "NurseryHub.h"
#include <queue>
#include <string>

/**
 * @class Manager
 * @brief Concrete staff class for managing task distribution in the Plant Nursery Simulator.
 * 
 * Inherits from Staff to handle task distribution, implementing the Command pattern (FR5) via receiveCommand to store unhandled commands.
 * Participates in the Chain of Responsibility Pattern (FR6) as the final handler, queuing commands when no staff are available 
 * and redistributing them via NurseryHub (FR7).
 */

class Manager : public Staff {
private:
    NurseryHub* nurseryHub; /**< Pointer to the NurseryHub mediator for task coordination (FR7). */
    std::queue<Command*> pendingCommands; /**< Queue of commands waiting for staff availability (FR6). */
public:
    /**
     * @brief Constructs a Manager with an ID and NurseryHub reference.
     * @param id Unique identifier for the manager.
     * @param hub Pointer to the NurseryHub mediator.
     */
    Manager(const std::string& id, NurseryHub* hub) : Staff(id), nurseryHub(hub) {}

    /**
     * @brief Receives and stores a command in pendingCommands for later assignment.
     * @param command Pointer to the Command to be executed.
     */
    void receiveCommand(Command* command) override;

    /**
     * @brief Handles a command request, queuing it if no staff are available.
     * @param command Pointer to the Command to handle.
     * @return True if the command is queued, false if ignored.
     */
    bool handleRequest(Command* command) override;

    /**
     * @brief Redistributes pending commands to available staff via NurseryHub.
     */
    void redistributeCommands();

};

#endif // MANAGER_H