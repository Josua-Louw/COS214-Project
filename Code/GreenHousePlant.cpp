#include "GreenHousePlant.h"
#include "CareStrategy.h"
#include "SeedState.h"

#include <iostream>

// Constructor
GreenHousePlant::GreenHousePlant(const std::string& name, double price, NurseryMediator* mediator, CareStrategy* care)
    : name(name), price(price), mediator_(mediator), strategy(care) {
    this->setState(new SeedState(this));
}

// Destructor
GreenHousePlant::~GreenHousePlant() {
    delete state;
}

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
	std::cout << "Finished Watering " << this->getName() << std::endl;
}

void GreenHousePlant::fertilizing(int time) {
	std::this_thread::sleep_for(std::chrono::seconds(time));
	std::cout << "Finished Fertilizing " << this->getName() << std::endl;
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

bool GreenHousePlant::getIsAlive() const{
	return isAlive.load();
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
	if (!state)
		delete state;
	state = newState;
}

void GreenHousePlant::killPlant(GreenHousePlant* plant) {
	isAlive.store(false);
}

