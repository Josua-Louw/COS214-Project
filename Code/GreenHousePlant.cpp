#include "GreenHousePlant.h"
#include "CareStrategy.h"

// Returns the name of the plant.
std::string GreenHousePlant::getName() const {
	return this->name;
}

void GreenHousePlant::applyCurrentCare() {
	if (strategy) {
		strategy->applyCare(*this);
	}
}

void GreenHousePlant::water() { applyCurrentCare(); }
void GreenHousePlant::feed()  { applyCurrentCare(); }

//Strategy helpers
void GreenHousePlant::adjustHydration(int d) {
	hydration += d;
}

void GreenHousePlant::adjustNutrition(int d) {
	nutrition += d;
}

void GreenHousePlant::setTimeForNextCare(int t) {
	timeForNextCare = t;
}

int  GreenHousePlant::getHydration() const{
	return hydration;
}

int  GreenHousePlant::getNutrition() const{
	return nutrition;
}
