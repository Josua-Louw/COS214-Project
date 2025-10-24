#include "PlantType.h"


PLANT_TYPE PlantType::getType() const {
	return PLANT_TYPE::ORDER_PLANT;
}

PlantImplementor* PlantType::clone() {
	return new PlantType(*this);
}
