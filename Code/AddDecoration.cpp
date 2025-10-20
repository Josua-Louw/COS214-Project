#include "AddDecoration.h"

/**
 * @file AddDecoration.cpp
 * @brief Implementation of the AddDecoration class.
 * 
 * @todo Implement the buildPart and checkType methods for adding decorative plants to an order.
 */

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
Order* AddDecoration::buildPart(Order* order, string itemName) {
	// TODO - implement AddDecoration::buildPart
	throw "Not yet implemented";
}

/**
 * @brief Checks if the given plant is of decorative type.
 * The method verifies if the plant matches the criteria for being classified as a decorative plant.
 * 
 * @param plant Pointer to the plant to be checked.
 * 
 * @return true if the plant is decorative, false otherwise.
 */
boolean AddDecoration::checkType(Plant* plant) {
	// TODO - implement AddDecoration::checkType
	throw "Not yet implemented";
}
