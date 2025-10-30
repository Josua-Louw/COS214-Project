#ifndef ADDPOT_H
#define ADDPOT_H

#include "OrderBuilder.h"

/**
 * @file AddPot.h
 * @brief Declaration of the AddPot class.
 * 
 * @class AddPot
 * @brief Concrete class for adding potted plants to an order in a greenhouse management system.
 * This class implements the buildPart method to add potted plants to an order based on the item name.
 * 
 * @note This class inherits from the OrderBuilder abstract class.
 * @implements buildPart
 * @implements checkType
 */

class AddPot : public OrderBuilder {


public:
	/**
	 * @brief Constructor for AddPot.
	 * @param gh Pointer to the GreenHouse instance.
	 */
	AddPot(GreenHouse* gh); 

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
	Order* buildPart(Order* order, std::string itemName);

	/**
	 * @brief Checks if the given plant is of potted type.
	 * The method verifies if the plant matches the criteria for being classified as a pot.
	 * 
	 * @param plant Pointer to the plant to be checked.
	 * 
	 * @return true if the plant is a pot, false otherwise.
	 */
	bool checkType(Item* item);
};

#endif
