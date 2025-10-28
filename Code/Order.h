#ifndef ORDER_H
#define ORDER_H

#include "Plant.h"
#include <vector>

class Customer;

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
	std::vector<Item*> items;
	Customer* customer = nullptr;

public:
	Order();

	~Order();

	Customer* getCustomer() const;

	void setCustomer(Customer* c);

	double getTotalCost() const;

	void addItem(Item* item);

	size_t getItemCount() const;

	void printOrder() const;
};

#endif
