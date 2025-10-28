#include "Customer.h"
#include "OrderBuilder.h"

void Customer::buy() {
	//Idea get list of available items from mediator according to the builder's type
	//use some randomization to select items to add to the order
	Order* order = new Order();
	order->setCustomer(this);
	for (OrderBuilder* builder : orderBuilders) {
		if (builder) {
			//find item's of builder's type from mediator
			order = builder->buildPart(order, itemNames.front());
			//NOTE: itemNames is temporary for testing
			itemNames.erase(itemNames.begin());
		}
	}
	order->printOrder();
	delete order;
}

Customer::~Customer() {
	// Clean up order builders if necessary
	for (auto builder : orderBuilders) {
		if (builder)
		{
			delete builder;
		}
	}
}