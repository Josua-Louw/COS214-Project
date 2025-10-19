#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer : Person {

private:
	OrderBuilder* orderBuilder;
	NurseryMediator* nurseryHub;

public:
	void buy();
};

#endif
