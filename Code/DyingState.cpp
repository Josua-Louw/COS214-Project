#include "DyingState.h"

// Implement care actions specific to the dying state
void DyingState::handleCare() {
	// TODO - implement DyingState::handleCare
	throw "Not yet implemented";
}

// Implement the logic to transition the plant to the next state
void DyingState::transitionToNext() {
	// TODO - implement DyingState::transitionToNext
	throw "Not yet implemented";
}

DyingState::DyingState(GreenHousePlant * plant, PlantState* previous) : PlantState(plant), previous(previous) {
	DyingState::transitionToNext();
}
