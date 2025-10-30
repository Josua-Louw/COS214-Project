#include "Customer.h"
#include "OrderBuilder.h"

Customer::Customer(std::string id, NurseryMediator* mediator, GreenHouse* gh)
	: Person(id), nurseryHub(mediator) {
	// Create a random set of order builders
	int numBuilders = rand() % 5 + 1; // Between 1 and 5 builders
	int seedPacketsInDecoratedOrder = 0;
	bool addedNewPlant = false;
	for (int i = 0; i < numBuilders; ++i) {
		// Randomly choose a builder type to add
		int builderType = rand() % 4;
		switch (builderType) {
		case 0:
			if (addedNewPlant && seedPacketsInDecoratedOrder >= 1) {
				// Skip adding another seed packet if limit reached
				continue;
			}
			orderBuilders.push_back(new AddSeed(gh));
			seedPacketsInDecoratedOrder = (addedNewPlant) ? seedPacketsInDecoratedOrder + 1 : 0;
			break;
		case 1:
			orderBuilders.push_back(new AddPot(gh));
			break;
		case 2:
			orderBuilders.push_back(new AddDecoration(gh));
			break;
		case 3:
			orderBuilders.push_back(new AddPlant(gh));
			seedPacketsInDecoratedOrder = 0;
			addedNewPlant = true;
			break;
		default:
			break;
		}
	}
}

void Customer::buy() {
	//Idea get list of available items from mediator according to the builder's type
	//use some randomization to select items to add to the order
	Order* order = new Order();
	order->setCustomer(this);
	for (OrderBuilder* builder : orderBuilders) {
		if (builder) {
			//find item's of builder's type from mediator
			//TODO: implement requestItemList in mediator
			std::vector<std::string> itemNames = nurseryHub->getPlantNamesByType(builder);
			if (itemNames.empty()) {
				continue;
			}
			//randomly select an item from the list
			int randomIndex = rand() % itemNames.size();
			std::string selectedItem = itemNames[randomIndex];
			//build part of the order with the selected item
			order = builder->buildPart(order, selectedItem);
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