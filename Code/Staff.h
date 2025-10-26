#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include "Command.h"
#include <vector>
#include <string>

/**
 * @class Staff
 * @brief Abstract base class for staff in the Plant Nursery Simulator, implementing Chain of Responsibility and Command Patterns.
 *
 * Represents staff members who handle tasks like plant care and customer interactions. The Chain of Responsibility Pattern (FR6) distributes commands to available staff via nextStaff, removing assigned staff from the chain. The Command Pattern (FR5) stores tasks in taskList for execution. Staff interacts with NurseryHub (Mediator, FR7) for task coordination.
 */
class Staff : public Person {
protected:
    Staff* nextStaff; /**< Pointer to the next staff in the chain (FR6). */
    std::vector<Command*> taskList; /**< List of commands assigned to the staff (FR5). */
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
     * @brief Handles a command request, checking availability and command type.
     * @param command Pointer to the Command to handle.
     * @return True if the command is handled, false if delegated or ignored.
     */
    virtual bool handleRequest(Command* command) = 0;

    /**
     * @brief Handles a command request, checking availability and command type.
     * @param command Pointer to the Command to handle.
     * @return True if the command is handled, false if delegated or ignored.
     */
    virtual bool handleRequest(Command* command) = 0;
    
    /**
     * @brief Sets the next staff in the chain for task delegation.
     * @param next Pointer to the next Staff member.
     */
    void setNextStaff(Staff* next) { nextStaff = next; }

    /**
     * @brief Gets the task list for testing purposes.
     * @return Const reference to the task list.
     */
    const std::vector<Command*>& getTaskList() const { return taskList; }

    /**
     * @brief Gets the next staff in the chain for testing purposes.
     * @return Pointer to the next Staff member.
     */
    Staff* getNextStaff() const { return nextStaff; }

    /**
     * @brief Gets the task list for testing purposes.
     * @return Const reference to the task list.
     */
    const std::vector<Command*>& getTaskList() const { return taskList; }
    
    /**
     * @brief Gets the next staff in the chain for testing purposes.
     * @return Pointer to the next Staff member.
     */
    Staff* getNextStaff() const { return nextStaff; }
    
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Staff() {
        for (Command* cmd : taskList) {
            delete cmd; // Clean up commands
        }
    }
};

#endif // STAFF_H