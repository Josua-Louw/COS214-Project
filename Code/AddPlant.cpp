#include "AddPlant.h"
#include <iostream>
#include <string>

/**
 * @file AddPlant.cpp
 * @brief Implementation of the AddPlant class.
 * 
 * @todo Implement the buildPart and checkType methods for adding plants to an order.
 */

 /**
  * @brief Builds the part of the order by adding plants based on the item name.
  * The method searches for plants in the greenhouse and adds them to the order.
  * The method checks the plant type and adds it to the order if it is a normal plant.
  * 
  * @param order Pointer to the current order.
  * @param itemName Name of the plant item to be added.
  * 
  * @return Pointer to the updated order.
  */
Order* AddPlant::buildPart(Order* order, std::string itemName) {
  if (!greenHouse || !order)
    return order;
    Item* found = greenHouse->findItem(itemName);
    if (found && checkType(found)) {
      order->addItem(found);
      std::cout << "Added plant: " << itemName << " to order.\n";
    }
    return order;
}

/**
 * @brief Checks if the given plant meets the criteria for being added to the order.
 * The method verifies if the plant matches the required type for inclusion in the order.
 * 
 * @param plant Pointer to the plant to be checked.
 * 
 * @return true if the plant is a normal plant, false otherwise.
 */
bool AddPlant::checkType(Item* item) {
  return (item && item->getType() == PLANT_TYPE::GREENHOUSE_PLANT);
}
