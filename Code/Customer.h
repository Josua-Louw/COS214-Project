#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "NurseryMediator.h"
#include "Order.h"
#include <vector>

class OrderBuilder;

class Customer : public Person {

private:
	NurseryMediator* nurseryHub;
	std::vector<OrderBuilder*> orderBuilders;


	//TEMPORARY - for testing
	std::vector<std::string> itemNames;

public:
	void buy();

	Customer(std::string id, NurseryMediator* mediator, std::vector<OrderBuilder*> builders)
		: Person(id), nurseryHub(mediator), orderBuilders(builders) {};

	//TEMPORARY CONSTRUCTOR FOR TESTING JUST TO ADD STRING VECTOR OF ITEMS TO ORDER
	Customer(std::string id, NurseryMediator* mediator, std::vector<OrderBuilder*> builders, std::vector<std::string> itemNames)
		: Person(id), nurseryHub(mediator), orderBuilders(builders), itemNames(itemNames) {};
	
	virtual ~Customer();
};

#endif
