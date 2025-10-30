#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "NurseryMediator.h"
#include "Order.h"
#include "AddSeed.h"
#include "AddPot.h"
#include "AddDecoration.h"
#include "AddPlant.h"
#include <vector>
#include <cstdlib> // For rand() and srand()

class OrderBuilder;

/**
 * @file Customer.h
 * @brief Declaration of the Customer class.
 * @details The Customer class represents a customer in the nursery system.
 * It inherits from the Person class and interacts with the NurseryMediator
 * to place orders using various OrderBuilder strategies.
 */

/**
 * @class Customer
 * @brief Represents a customer who can place orders in the nursery system.
 * @details The Customer class utilizes multiple OrderBuilder instances to
 * create orders for different types of items available in the greenhouse.
 * It communicates with the NurseryMediator to retrieve item lists and place orders.
 * @note The Customer class is responsible for managing its own order builders
 * and coordinating the order creation process.
 * @note Represents the director in the Builder design pattern.
 */

class Customer : public Person {
private:
	// List of order builders used by the customer
	std::vector<OrderBuilder*> orderBuilders;
	// Mediator for communication with the nursery system
	NurseryMediator* nurseryHub;

	//TEMPORARY - for testing
	std::vector<std::string> itemNames;

public:
	/**
	 * @brief Initiates the buying process for the customer.
	 * @details The method creates a new order and uses the assigned
	 * OrderBuilder instances to add items to the order based on available items.
	 */
	void buy();
	//Constructor to generate a random set of order builders
	/**
	 * @brief Constructs a Customer with a random set of OrderBuilders.
	 * @param id Unique identifier for the customer.
	 * @param mediator Pointer to the NurseryMediator instance.
	 * @param gh Pointer to the GreenHouse instance, for the order builders.
	 * @note The constructor randomly selects between 1 to 5 OrderBuilder types
	 * to create a diverse order-building strategy for the customer.
	 */
	Customer(std::string id, NurseryMediator* mediator, GreenHouse* gh);
	/**
	 * @brief Constructs a Customer with specified OrderBuilders.
	 * @param id Unique identifier for the customer.
	 * @param mediator Pointer to the NurseryMediator instance.
	 * @param builders Vector of OrderBuilder pointers to be used by the customer.
	 * @note This constructor allows for explicit specification of the
	 * OrderBuilder instances to be used for order creation.
	 */
	Customer(std::string id, NurseryMediator* mediator, std::vector<OrderBuilder*> builders)
		: Person(id), nurseryHub(mediator), orderBuilders(builders) {};

	//TEMPORARY CONSTRUCTOR FOR TESTING JUST TO ADD STRING VECTOR OF ITEMS TO ORDER
	Customer(std::string id, NurseryMediator* mediator, std::vector<OrderBuilder*> builders, std::vector<std::string> itemNames)
		: Person(id), nurseryHub(mediator), orderBuilders(builders), itemNames(itemNames) {};
	/**
	 * @brief Destructor for the Customer class.
	 * @details Cleans up dynamically allocated OrderBuilder instances.
	 * @note Ensures proper memory management by deleting each OrderBuilder in the orderBuilders vector.
	 */
	virtual ~Customer();
};

#endif
