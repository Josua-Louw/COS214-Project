#include "SellCommand.h"
#include "Plant.h"
#include "Order.h"
#include "GreenHouse.h"

/**
 * @file SellCommand.cpp
 * @brief Implementation of the SellCommand class.
 * 
 * Executes the sale of a plant as part of a customer order, updating the greenhouse inventory and order status. Assigned to SalesManager via NurseryHub (Mediator, FR7). Integrates with the Builder Pattern (OrderBuilder, FR8), Decorator Pattern (Order customization, FR10), and Composite Pattern (GreenHouse, FR1).
 */

/**
 * @brief Executes the sale, updating inventory and order status.
 * 
 * Adds the plant to the order and removes it from the greenhouse inventory by calling sell on the plant (as a GreenHouse leaf). Updates the order's total cost, supporting customer transactions (FR5, FR8, FR10).
 */
void SellCommand::execute() {
    if (plant && order) {
        order->addPlant(plant); // Add plant to the order (FR8, FR10)
        GreenHouse* plantAsGreenhouse = plant; // Plant publicly inherits from GreenHouse
        plantAsGreenhouse->sell(plant); // Remove plant from inventory and get price (FR1)
    }
}