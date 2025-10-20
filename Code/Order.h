#ifndef ORDER_H
#define ORDER_H

/**
 * @file Order.h
 * @brief Declaration of the Order class.
 * 
 * @class Order
 * @brief Class representing an order in a greenhouse management system.
 * This class manages a collection of plants included in the order and provides functionality
 * to calculate the total cost of the order.
 */

class Order {

private:
	vector<Plant*> plants;

public:
	double getTotalCost();

	void addPlant(Plant* plant);
};

#endif
