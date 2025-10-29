#include "GreenHousePlant.h"
#include "CareStrategy.h"
#include "SeedState.h"

#include <iostream>
#include <memory>

using CommandPtr = std::shared_ptr<Command>;
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


std::vector<CommandPtr> GreenHousePlant::applyCurrentCare() {
	if (strategy != nullptr) {
		return strategy->applyCare(*this);
	} else {
		return {};
	}
}

CommandPtr GreenHousePlant::water(int time) {
	auto cmd = std::make_shared<WaterPlant>(this, time);
	if (mediator_) mediator_->assign(cmd);
	return cmd;
}

CommandPtr GreenHousePlant::feed(int time) {
	auto cmd = std::make_shared<FertilizePlant>(this,time);
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

void GreenHousePlant::setWaterSuccess(bool success) {
	waterSuccessful.store(success, std::memory_order_relaxed);
}

void GreenHousePlant::setFertilizingSuccess(bool success) {
	fertilizingSuccessful.store(success, std::memory_order_relaxed);
}

void GreenHousePlant::setFertilizingBusy(bool busy) {
	fertilizingCareBusy.store(busy, std::memory_order_relaxed);
}

void GreenHousePlant::setWaterBusy(bool busy) {
	waterCareBusy.store(busy, std::memory_order_relaxed);
}

bool GreenHousePlant::getWaterSuccess() const{
	return waterSuccessful.load();
}

bool GreenHousePlant::getFertilizingSuccess() const{
	return fertilizingSuccessful.load();
}

bool GreenHousePlant::getWaterBusy() const{
	return waterCareBusy.load();
}

bool GreenHousePlant::getFertilizingBusy() const{
	return fertilizingCareBusy.load();
}

bool GreenHousePlant::getIsAlive() const{
	return isAlive.load();
}

void GreenHousePlant::markCareStarted(std::string type) {
	if (type == "FertilizePlant") {
		fertilizingSuccessful.store(false, std::memory_order_relaxed);
		fertilizingCareBusy.store(true, std::memory_order_relaxed);
	} else {
		waterSuccessful.store(false, std::memory_order_relaxed);
		waterCareBusy.store(true, std::memory_order_relaxed);
	}
}

void GreenHousePlant::markCareFinished(bool success, std::string type) {
	if (type == "FertilizePlant") {
		fertilizingSuccessful.store(success, std::memory_order_relaxed);
		fertilizingCareBusy.store(false, std::memory_order_relaxed);
	} else {
		waterSuccessful.store(success, std::memory_order_relaxed);
		waterCareBusy.store(false, std::memory_order_relaxed);
	}
}

void GreenHousePlant::setState(PlantState * newState) {
	if (state)
		delete state;
	state = newState;
}

void GreenHousePlant::killPlant() {
	isAlive.store(false);
}

