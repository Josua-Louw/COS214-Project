#include "SellCommand.h"
#include "Order.h"
#include "Customer.h"
#include "OrderBuilder.h"

/**
 * @file SellCommand.cpp
 * @brief Implementation of the SellCommand class.
 * 
 * Executes the sale of a plant as part of a customer order, updating the greenhouse inventory and order status. Assigned to SalesManager via NurseryHub (Mediator, FR7). Integrates with the Builder Pattern (OrderBuilder, FR8), Decorator Pattern (Order customization, FR10), and Composite Pattern (GreenHouse, FR1).
 */

std::string SellCommand::getType() {
    return "SellCommand";
}

/**
 * @brief Executes the sale, updating inventory and order status.
 * 
 * Adds the plant to the order and removes it from the greenhouse inventory by calling sell on the plant (as a GreenHouse leaf). Updates the order's total cost, supporting customer transactions (FR5, FR8, FR10).
 */
void SellCommand::execute() {
    if (!plant || !order) return;

    //lazy resolve the composite root if not provided
    if (!inventory) {
        if (Customer* c = order->getCustomer()) {
            if (OrderBuilder* b = c->anyBuilder()) {
                inventory = b->getGreenHouse();
            }
        }
    }
    if (!inventory) return;

    order->addItem(plant);
    inventory->sell(plant);
}
