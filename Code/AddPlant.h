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

class AddPlant : OrderBuilder {


protected:
	Order* buildPart(Order* order, std::string itemName);

	bool checkType(Plant* plant);
};

#endif
