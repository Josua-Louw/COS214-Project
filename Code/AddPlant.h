#ifndef ADDPLANT_H
#define ADDPLANT_H

#include "OrderBuilder.h"

/**
 * @file AddPlant.h
 * @brief Declaration of the AddPlant class.
 * 
 * @class AddPlant
 * @brief Concrete class for adding plants to an order in a greenhouse management system.
 * This class implements the buildPart method to add plants to an order based on the item name.
 * 
 * @note This class inherits from the OrderBuilder abstract class.
 * @implements buildPart
 * @implements checkType
 */

class AddPlant : public OrderBuilder {

public:
	/**
	 * @brief Constructor for AddPlant.
	 * @param gh Pointer to the GreenHouse instance.
	 */
	AddPlant(GreenHouse* gh); 

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
	Order* buildPart(Order* order, std::string itemName);

	/**
	 * @brief Checks if the given plant meets the criteria for being added to the order.
	 * The method verifies if the plant matches the required type for inclusion in the order.
	 * 
	 * @param plant Pointer to the plant to be checked.
	 * 
	 * @return true if the plant is a normal plant, false otherwise.
	 */
	bool checkType(Item* item);
};

#endif
