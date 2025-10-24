#include "Pot.h"

PLANT_TYPE Pot::getType() const {
	return PLANT_TYPE::POT;
}

PlantImplementor* Pot::clone() {
	return new Pot(*this);
}
