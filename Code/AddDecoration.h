#ifndef ADDDECORATION_H
#define ADDDECORATION_H

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

class AddDecoration : OrderBuilder {


protected:
	Order* buildPart(Order* order, string itemName);

	boolean checkType(Plant* plant);
};

#endif
