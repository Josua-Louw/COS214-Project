#include "SenescenceState.h"
#include <iostream>

// Implement the logic to transition the plant to the next state
void SenescenceState::transitionToNext() {
	std::thread([this]() {
		std::cout << "\033[1;32mSenescence start\033[0m " << plant_->getName() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));
		std::cout << "Senescence fail " << plant_->getName() << std::endl;
		plant_->setState(new DeadState(plant_));
	}).detach();
}

SenescenceState::SenescenceState(GreenHousePlant * plant) : PlantState(plant) {
	SenescenceState::transitionToNext();
}
