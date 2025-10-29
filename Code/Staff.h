#ifndef STAFF_H
#define STAFF_H

#include "Person.h"
#include "Command.h"
#include <vector>
#include <string>
#include <atomic>
#include <memory>
using CommandPtr = std::shared_ptr<Command>;
/**
 * @class Staff
 * @brief Abstract base class for staff in the Plant Nursery Simulator, implementing Chain of Responsibility and Command Patterns.
 *
 * Represents staff members who handle tasks like plant care and customer interactions. The Chain of Responsibility Pattern (FR6) distributes commands to available staff via nextStaff, removing assigned staff from the chain. The Command Pattern (FR5) stores tasks in taskList for execution. Staff interacts with NurseryHub (Mediator, FR7) for task coordination.
 */
class Staff : public Person {
protected:
    Staff* nextStaff; /**< Pointer to the next staff in the chain (FR6). */
    std::atomic<bool> staffBusy{false};
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
    virtual void receiveCommand(CommandPtr command) = 0;

    /**
     * @brief Gets the next staff in the chain for testing purposes.
     * @return Pointer to the next Staff member.
     */
    Staff* getNextStaff() const { return nextStaff; }
    
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Staff() override = default;
    /**
     * @brief Adds a staff member to the beginning of the chain.
     * @param staff Pointer to the Staff member to add.
     * @note 'this' will be at the end of the chain.
     */

    void addStaffMember(Staff* staff) {
        if (staff == nullptr) {
            return;
        }
        staff->nextStaff = this;
    }
};

#endif // STAFF_H