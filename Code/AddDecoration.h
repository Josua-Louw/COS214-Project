#ifndef ADDDECORATION_H
#define ADDDECORATION_H

#include "OrderBuilder.h"
#include "GreenHouse.h"

/**
 * @file AddDecoration.h
 * @brief Declaration of the AddDecoration class.
 * 
 * @class AddDecoration
 * @brief Concrete class for adding decorative plants to an order in a greenhouse management system.
 * This class implements the buildPart method to add decorative plants to an order based on the item name.
 * 
 * @note This class inherits from the OrderBuilder abstract class.
 * @implements buildPart
 * @implements checkType
 */

class AddDecoration : public OrderBuilder {


public:
	/**
	 * @brief Constructor for AddDecoration.
	 * @param gh Pointer to the GreenHouse instance.
	 */
	AddDecoration(GreenHouse* gh);

	/**
	 * @brief Builds the part of the order by adding decorative plants based on the item name.
	 * @param order Pointer to the current order.
	 * @param itemName Name of the decorative plant item to be added.
	 * @return Pointer to the updated order.
	 */
	Order* buildPart(Order* order, std::string itemName);

	/**
	 * @brief Checks if the given plant is of decorative type.
	 * @param item Pointer to the plant to be checked.
	 * @return true if the plant is decorative, false otherwise.
	 */
	bool checkType(Item* item);
};

#endif
