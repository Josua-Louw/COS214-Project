#include "SenescenceState.h"
#include <iostream>

// Implement the logic to transition the plant to the next state
void SenescenceState::transitionToNext() {
	std::thread([this]() {
		std::cout << "\033[1;32mSenescence start\033[0m" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));
		std::cout << "Senescence fail" << std::endl;
		plant_->setState(new DyingState(plant_, DyingState::PrevKind::Dead));
	}).detach();
}

SenescenceState::SenescenceState(GreenHousePlant * plant) : PlantState(plant) {
	SenescenceState::transitionToNext();
}
