#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"
#include "OrderBuilder.h"
#include "NurseryMediator.h"

class Customer : Person {

private:
	OrderBuilder* orderBuilder;
	NurseryMediator* nurseryHub;

public:
	void buy();
};

#endif
