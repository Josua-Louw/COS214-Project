#ifndef COMMAND_H
#define COMMAND_H

/**
 * @class Command
 * @brief Abstract base class for the Command Pattern in the Plant Nursery Simulator.
 * 
 * Encapsulates staff tasks (e.g., watering, fertilizing, selling) as command objects, allowing tasks to be stored, executed, and potentially undone. Commands are assigned to Staff via NurseryHub (Mediator) and stored in Staff's taskList. This pattern decouples task requests from their execution, enabling flexible task management.
 */
class Command {
public:
    /**
     * @brief Executes the command, performing the specific task.
     * 
     * Pure virtual method implemented by concrete command classes (e.g., WaterPlant, SellCommand).
     */
    virtual void execute() = 0;
    
    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Command() {}
};

#endif // COMMAND_H