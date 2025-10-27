#include "SenescenceState.h"

// Implement the logic to transition the plant to the next state
void SenescenceState::transitionToNext() {
	std::thread([this]() {
		std::this_thread::sleep_for(std::chrono::seconds(20));
		plant_->setState(new DyingState(plant_,nullptr));
	}).detach();
}

SenescenceState::SenescenceState(GreenHousePlant * plant) : PlantState(plant) {
	SenescenceState::transitionToNext();
}
