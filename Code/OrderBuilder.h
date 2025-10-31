#ifndef ORDERBUILDER_H
#define ORDERBUILDER_H

#include "GreenHouse.h"
class Item;

class Order;

/**
 * @file OrderBuilder.h
 * @brief Declaration of the OrderBuilder abstract class.
 * 
 * @class OrderBuilder
 * @brief Abstract class for building parts of an order in a greenhouse management system.
 * This class defines the interface for building specific parts of an order based on plant types.
 * 
 * @note This class needs a pointer to a GreenHouse object to access plant data.
 * @note Derived classes must implement the buildPart and checkType methods.
 * 
 * @note The buildPart method falls under the Builder Design Pattern.
 * @note The checkType method falls under the Template Method Design Pattern which is a step in the process.
 */

class OrderBuilder {

protected:
	GreenHouse* greenHouse;

public:
	/**
	 * @brief Constructor for OrderBuilder.
	 * @param gh Pointer to the GreenHouse instance.
	 */
	OrderBuilder(GreenHouse* gh) : greenHouse(gh) {} 
	/**
	 * @brief Builds the part of the order based on the item name.
	 * The method searches for plants in the greenhouse and adds them to the order
	 * if they match the criteria defined in checkType.
	 * 
	 * @param order Pointer to the current order.
	 * @param itemName Name of the item to be added.
	 * 
	 * @return Pointer to the updated order.
	 */
	virtual Order* buildPart(Order* order, std::string itemName) = 0;
	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~OrderBuilder() = default;

	virtual bool checkType(Item* item) = 0;
};

#endif
