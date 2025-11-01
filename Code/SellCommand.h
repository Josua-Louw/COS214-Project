#ifndef SELL_COMMAND_H
#define SELL_COMMAND_H

#include "Command.h"
#include "Plant.h"
#include "Order.h"

/**
 * @class SellCommand
 * @brief Concrete command for selling a plant in the Plant Nursery Simulator.
 * 
 * Implements the Command Pattern to encapsulate the task of processing a plant sale. Assigned to SalesManager via NurseryHub, it interacts with a Plant and Order to complete a customer transaction, updating inventory and supporting the Builder/Decorator Patterns for order customization.
 */
class SellCommand : public Command {
private:
    Plant* plant; /**< The plant to be sold. */
    Order* order; /**< The customer order containing the plant. */
public:
    /**
     * @brief Constructs a SellCommand for a specific plant and order.
     * @param plant Pointer to the Plant to be sold.
     * @param order Pointer to the Order containing the plant.
     */
    SellCommand(Plant* plant, Order* order) : plant(plant), order(order) {}

    std::string getType();
    
    /**
     * @brief Executes the sale, updating inventory and order status.
     */
    void execute() override;
};

#endif // SELL_COMMAND_H