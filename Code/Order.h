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
 * @warning Only use this class as a pointer because there is no copy constructor or assignment operator defined.
 */

class Order {

private:
	std::vector<OrderPlant*> items;
	Customer* customer = nullptr;
	PlantType* activePlant = nullptr;
public:
	/**
	 * @brief Constructor for Order.
	 */
	Order();
	/**
	 * @brief Destructor for Order.
	 */
	~Order();
	/**
	 * @brief Destructor for Order.
	 */
	Customer* getCustomer() const;
	/**
	 * @brief Sets the customer for the order.
	 * @param c Pointer to the Customer object.
	 */
	void setCustomer(Customer* c);
	/**
	 * @brief Calculates the total cost of the order.
	 * @return The total cost as a double.
	 */
	double getTotalCost() const;
	/**
	 * @brief Adds an item to the order.
	 * @param item Pointer to the OrderPlant to be added.
	 */
	void addItem(Item* item);
	/**
	 * @brief Gets the number of items in the order.
	 * @return The number of items as a size_t.
	 */
	size_t getItemCount() const;
	/**
	 * @brief Prints the order details.
	 */
	void printOrder() const;
};

#endif
