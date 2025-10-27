#ifndef ORDERBUILDER_H
#define ORDERBUILDER_H

#include "GreenHouse.h"

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

	virtual bool checkType(Item* item) = 0;

public:
	OrderBuilder(GreenHouse* gh) : greenHouse(gh) {} 

	virtual Order* buildPart(Order* order, std::string itemName) = 0;

	virtual ~OrderBuilder() = default;
};

#endif
