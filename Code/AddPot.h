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

class AddPot : OrderBuilder {


protected:
	Order* buildPart(Order* order, std::string itemName);

	bool checkType(Plant* plant);
};

#endif
