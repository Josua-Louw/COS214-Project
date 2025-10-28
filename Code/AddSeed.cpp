#include "AddSeed.h"
#include "AddPlant.h"
#include "Order.h"
#include "Item.h"

#include <iostream>
#include <string>

/**
 * @file AddSeed.cpp
 * @brief Implementation of the AddSeed class.
 * 
 * @todo Implement the buildPart and checkType methods for adding seed plants to an order.
 */

AddSeed::AddSeed(GreenHouse* gh) 
       : OrderBuilder(gh) {

}

/**
 * @brief Builds the part of the order by adding seed plants based on the item name.
 * The method searches for seed plants in the greenhouse and adds them to the order.
 * The method checks the plant type and adds it to the order if it matches the seed type.
 * 
 * @param order Pointer to the current order.
 * @param itemName Name of the seed plant item to be added.
 *  
 * @return Pointer to the updated order.
*/ 
Order* AddSeed::buildPart(Order* order, std::string itemName) {
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
    	std::cout << "Added seed: " << itemName << " to order.\n";
    } else {
    	std::cout << "Warning: '" << itemName << "' not found in greenhouse.\n";
    }
    return order;
}

/**
 * @brief Checks if the given plant is of seed type.
 * The method verifies if the plant matches the criteria for being classified as a seed plant.
 * 
 * @param plant Pointer to the plant to be checked.
 * 
 * @return true if the plant is a seed, false otherwise.
 */
bool AddSeed::checkType(Item* item) {
  return (item && item->getType() == PLANT_TYPE::SEED_PACKET);
}
