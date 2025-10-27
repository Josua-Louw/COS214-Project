#include "GreenHousePlant.h"
#include "CareStrategy.h"

// Returns the name of the plant.
std::string GreenHousePlant::getName() const {
	return this->name;
}

double GreenHousePlant::getPrice() const { return price; }

PlantImplementor* GreenHousePlant::clone() {
	//implement later
	return nullptr;
}

PLANT_TYPE GreenHousePlant::getType() const {
	return PLANT_TYPE::GREENHOUSE_PLANT;
}

GreenHousePlant::~GreenHousePlant() = default;

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

bool GreenHousePlant::getSuccess() const{
	return careSuccessful.load();
}

bool GreenHousePlant::getBusy() const{
	return careBusy.load();
}

void GreenHousePlant::markCareStarted() {
	careSuccessful.store(false, std::memory_order_relaxed);
	careBusy.store(true, std::memory_order_release);
	if (mediator_) mediator_->notify(this, "CARE_STARTED", name);
}

void GreenHousePlant::markCareFinished(bool success) {
	careSuccessful.store(success, std::memory_order_relaxed);
	careBusy.store(false, std::memory_order_release);
	if (mediator_) {
		mediator_->notify(this, success ? "CARE_FINISHED_OK" : "CARE_FINISHED_FAIL", name);
	}
}

void GreenHousePlant::setState(PlantState * newState) {
	delete state;
	state = newState;
}

