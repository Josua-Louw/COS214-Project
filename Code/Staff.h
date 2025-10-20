#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include "Command.h"
#include <vector>

/**
 * @class Staff
 * @brief Abstract base class for staff in the Plant Nursery Simulator, implementing Chain of Responsibility and Command Patterns.
 * 
 * Represents staff members who handle tasks like plant care and customer interactions. The Chain of Responsibility Pattern distributes commands to available staff via nextStaff, removing assigned staff from the chain. The Command Pattern stores tasks in taskList for execution. Staff interacts with NurseryHub (Mediator) for task coordination.
 */
class Staff : public Person {
protected:
    Staff* nextStaff; /**< Pointer to the next staff in the chain (Chain of Responsibility). */
    std::vector<Command*> taskList; /**< List of commands assigned to the staff (Command Pattern). */
public:
    /**
     * @brief Constructs a Staff member with an ID.
     * @param id Unique identifier for the staff.
     */
    Staff(const std::string& id) : Person(id), nextStaff(nullptr) {}
    
    /**
     * @brief Receives and stores a command in taskList for execution.
     * @param command Pointer to the Command to be executed.
     */
    virtual void receiveCommand(Command* command) = 0;
    
    /**
     * @brief Sets the next staff in the chain for task delegation.
     * @param next Pointer to the next Staff member.
     */
    void setNextStaff(Staff* next) { nextStaff = next; }
    
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Staff() {}
};

#endif // STAFF_H