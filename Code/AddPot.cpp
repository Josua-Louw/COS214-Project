#include "AddPot.h"
#include "AddPlant.h"
#include "Order.h"
#include "Item.h"

#include <iostream>
#include <string>

/**
 * @file AddPot.cpp
 * @brief Implementation of the AddPot class.
 * 
 * @todo Implement the buildPart and checkType methods for adding potted plants to an order.
 */

AddPot::AddPot(GreenHouse* gh) 
      : OrderBuilder(gh) {

}

 /**
  * @brief Builds the part of the order by adding potted plants based on the item name.
  * The method searches for potted plants in the greenhouse and adds them to the order.
  * The method checks the plant type and adds it to the order if it matches the pot type.
  * 
  * @param order Pointer to the current order.
  * @param itemName Name of the pot item to be added.
  * 
  * @return Pointer to the updated order.
  */
Order* AddPot::buildPart(Order* order, std::string itemName) {
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
    std::cout << "Added pot: " << itemName << " to order.\n";
  } else {
    std::cout << "Warning: '" << itemName << "' not found in greenhouse.\n";
  }
  return order;
}

/**
 * @brief Checks if the given plant is of potted type.
 * The method verifies if the plant matches the criteria for being classified as a pot.
 * 
 * @param plant Pointer to the plant to be checked.
 * 
 * @return true if the plant is a pot, false otherwise.
 */
bool AddPot::checkType(Item* item) {
  return (item && item->getType() == PLANT_TYPE::POT);
}
