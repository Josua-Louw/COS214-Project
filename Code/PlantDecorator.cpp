#include "PlantDecorator.h"

double PlantDecorator::getPrice() const {
	if (component != nullptr)
	{
		return cost + component->getPrice();
	}
	return cost;
}

void PlantDecorator::decorate(OrderPlant* orderPlant) {
	if (orderPlant == nullptr)
	{
		return;
	}
	
	if (component != nullptr)
	{
		if (component->getType() == PLANT_TYPE::SEED_PACKET)
		{
			if (orderPlant->getType() == PLANT_TYPE::SEED_PACKET)
			{
				throw "Cannot decorate plant decorator with more than one seed packet. (Attempted to add 2 seed packets to one decorator)";
			} 
			else 
			{
				orderPlant->decorate(component);
				component = orderPlant;
			}
		}
		else 
		{
			component->decorate(orderPlant);
		}
	}
	else 
	{
		component = orderPlant;
	}
}

PlantDecorator::~PlantDecorator() {
	if (component != nullptr) {
		delete component;
		component = nullptr;
	}
}