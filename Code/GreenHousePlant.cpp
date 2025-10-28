#include "GreenHousePlant.h"
#include "CareStrategy.h"

#include <iostream>

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


std::vector<Command*> GreenHousePlant::applyCurrentCare() {
	if (strategy != nullptr) {
		return strategy->applyCare(*this);
	} else {
		return {};
	}
}

Command* GreenHousePlant::water(int time) {
	Command* cmd = new WaterPlant(this, time);
	if (mediator_) mediator_->assign(cmd);
	return cmd;
}

Command* GreenHousePlant::feed(int time) {
	Command* cmd = new FertilizePlant(this,time);
	if (mediator_) mediator_->assign(cmd);
	return cmd;
}

void GreenHousePlant::watering(int time) {
	std::this_thread::sleep_for(std::chrono::seconds(time));
	std::cout << "Finished Watering\n";
}

void GreenHousePlant::fertilizing(int time) {
	std::this_thread::sleep_for(std::chrono::seconds(time));
	std::cout << "Finished Fertilizing\n";
}

void GreenHousePlant::setSuccess(bool success) {
	careSuccessful.store(success, std::memory_order_release);
}

void GreenHousePlant::setBusy(bool busy) {
	careBusy.store(busy, std::memory_order_release);
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
}

void GreenHousePlant::markCareFinished(bool success) {
	careSuccessful.store(success, std::memory_order_relaxed);
	careBusy.store(false, std::memory_order_release);
}

void GreenHousePlant::setState(PlantState * newState) {
	delete state;
	state = newState;
}

