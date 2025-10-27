#include "DyingState.h"



// Implement the logic to transition the plant to the next state
void DyingState::transitionToNext() {
	std::thread([this]() {
		std::this_thread::sleep_for(std::chrono::seconds(20));
		plant_->applyCurrentCare();
		if (plant_->getSuccess()) {
			if (previous == nullptr)
				plant_->setState(new DeadState(plant_));
			else
				plant_->setState(previous);
		} else if (plant_->getBusy()) {
			while (!plant_->getSuccess()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			if (previous == nullptr)
				plant_->setState(new DeadState(plant_));
			else
				plant_->setState(previous);
		} else {
			plant_->setState(new DeadState(plant_));
		}
	}).detach();
}

DyingState::DyingState(GreenHousePlant * plant, PlantState* previous) : PlantState(plant), previous(previous) {
	DyingState::transitionToNext();
}
