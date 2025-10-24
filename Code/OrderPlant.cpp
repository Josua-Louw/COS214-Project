#include "OrderPlant.h"

std::string OrderPlant::getName() const {
    return name;
}

// Copy constructor
OrderPlant::OrderPlant(const OrderPlant& other) 
: PlantImplementor(other), cost(other.cost), name(other.name) {}