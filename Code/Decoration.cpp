#include "Decoration.h"

PLANT_TYPE Decoration::getType() const {
	return PLANT_TYPE::DECORATION;
}

PlantImplementor* Decoration::clone() {
	return new Decoration(*this);
}
