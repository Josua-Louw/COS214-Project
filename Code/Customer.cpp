#include "Customer.h"
#include "OrderBuilder.h"
#include "NurseryHub.h"
#include "GreenHouse.h"
#include "SellCommand.h"
#include <memory>
#include <iostream>

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

//I tried to update buy() but I am not sure how to implement this exactly so I am commenting out this version for now.
// void Customer::buy() {
// 	if (!nurseryHub) return;
//
// 	Order* order = new Order();
// 	order->setCustomer(this);
//
// 	for (OrderBuilder* builder : orderBuilders) {
// 		if (!builder) continue;
// 		if (!itemNames.empty()) {
// 			order = builder->buildPart(order, itemNames.front());
// 			itemNames.erase(itemNames.begin());
// 		}
// 	}
//
// 	OrderBuilder* any = anyBuilder();
// 	GreenHouse* root = any ? any->getGreenHouse() : nullptr;
// 	if (root) {
// 		for (const std::string& name : itemNames) {
// 			if (Item* it = root->findItem(name)) {
// 				if (auto* plant = dynamic_cast<Plant*>(it)) {
// 					auto cmd = std::make_shared<SellCommand>(plant, order);
// 					nurseryHub->assign(cmd);
// 				}
// 			}
// 		}
// 	}
//
// 	order->printOrder();
// 	delete order;
// }


Customer::~Customer() {
	// Clean up order builders if necessary
	for (auto builder : orderBuilders) {
		if (builder)
		{
			delete builder;
		}
	}
}