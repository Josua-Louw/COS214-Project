#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "NurseryMediator.h"
#include <string>

class OrderBuilder;

class Customer : public Person {

private:
	OrderBuilder* orderBuilder;
	NurseryMediator* nurseryHub;

public:
	void buy();

	Customer(std::string id);
};

#endif
