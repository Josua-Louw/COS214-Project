#ifndef SALES_MANAGER_H
#define SALES_MANAGER_H

#include "Staff.h"

/**
 * @class SalesManager
 * @brief Concrete staff class for handling customer sales in the Plant Nursery Simulator.
 * 
 * Inherits from Staff to manage sales tasks, implementing the Command Pattern via receiveCommand to process SellCommand tasks. Participates in the Chain of Responsibility Pattern by receiving delegated tasks via nextStaff. Interacts with Customer and NurseryHub (Mediator) to facilitate sales and order processing.
 */
class SalesManager : public Staff {
public:
    /**
     * @brief Constructs a SalesManager with an ID.
     * @param id Unique identifier for the SalesManager.
     */
    SalesManager(const std::string& id) : Staff(id) {}
    
    /**
     * @brief Receives and executes a SellCommand, processing a customer order.
     * @param command Pointer to the Command (e.g., SellCommand) to execute.
     */
    void receiveCommand(Command* command) override;
};

#endif // SALES_MANAGER_H