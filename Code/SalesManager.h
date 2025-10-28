#ifndef SALES_MANAGER_H
#define SALES_MANAGER_H

#include "Staff.h"
#include "NurseryMediator.h"

/**
 * @class SalesManager
 * @brief Concrete staff class for handling customer sales in the Plant Nursery Simulator.
 *
 * Inherits from Staff to manage sales tasks, implementing the Command Pattern (FR5) via receiveCommand to process SellCommand tasks. Participates in the Chain of Responsibility Pattern (FR6) by receiving delegated tasks via nextStaff. Interacts with Customer and NurseryHub (Mediator, FR7) to facilitate sales and order processing.
 */
class SalesManager : public Staff {
private:
    NurseryMediator* nurseryHub; /**< Mediator for notifications (FR7). */
public:
    /**
     * @brief Constructs a SalesManager with an ID and NurseryHub.
     * @param id Unique identifier for the SalesManager.
     * @param hub Pointer to the NurseryHub mediator.
     */
    SalesManager(const std::string& id, NurseryMediator* hub) : Staff(id), nurseryHub(hub) {}

    /**
     * @brief Receives and executes a SellCommand, processing a customer order.
     * @param command Pointer to the Command (e.g., SellCommand) to execute.
     */
    void receiveCommand(Command* command) override;
};

#endif // SALES_MANAGER_H