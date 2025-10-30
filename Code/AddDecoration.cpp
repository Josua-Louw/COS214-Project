#include "AddDecoration.h"
#include "Order.h"
#include "Item.h"

#include <iostream>
#include <string>

/**
 * @file AddDecoration.cpp
 * @brief Implementation of the AddDecoration class.
 * 
 * @todo Implement the buildPart and checkType methods for adding decorative plants to an order.
 */

AddDecoration::AddDecoration(GreenHouse* gh) 
              : OrderBuilder(gh) {

}
            
 /**
  * @brief Builds the part of the order by adding decorative plants based on the item name.
  * The method searches for decorative plants in the greenhouse and adds them to the order.
  * The method checks the plant type and adds it to the order if it matches the decorative type.
  * 
  * @param order Pointer to the current order.
  * @param itemName Name of the decorative plant item to be added.
  * 
  * @return Pointer to the updated order.
  */
Order* AddDecoration::buildPart(Order* order, std::string itemName) {
  if (!greenHouse || !order){
    return order;
  }
  Item* found = nullptr;
  if (greenHouse){
    found = greenHouse->findItem(itemName);
  }
  if (!found){
    return order;
  }
  if (found && checkType(found)) {
    order->addItem(found);
    std::cout << "Added decoration: " << itemName << " to order.\n";
  } else {
    std::cout << "Warning: '" << itemName << "' not found in greenhouse.\n";
  }
  return order;
}

/**
 * @brief Checks if the given plant is of decorative type.
 * The method verifies if the plant matches the criteria for being classified as a decorative plant.
 * 
 * @param item Pointer to the plant to be checked.
 * 
 * @return true if the plant is decorative, false otherwise.
 */
bool AddDecoration::checkType(Item* item) {
  return (item && item->getType() == PLANT_TYPE::DECORATION);
}
