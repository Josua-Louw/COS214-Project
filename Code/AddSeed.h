#ifndef ADDSEED_H
#define ADDSEED_H

#include "OrderBuilder.h"

/**
 * @file AddSeed.h
 * @brief Declaration of the AddSeed class.
 * 
 * @class AddSeed
 * @brief Concrete class for adding seed plants to an order in a greenhouse management system.
 * This class implements the buildPart method to add seed plants to an order based on the item name.
 * 
 * @note This class inherits from the OrderBuilder abstract class.
 * @implements buildPart
 * @implements checkType
 */

class AddSeed : public OrderBuilder {

protected:
	Order* buildPart(Order* order, std::string itemName);

	bool checkType(Item* item);
};

#endif
