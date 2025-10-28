#include "DeadState.h"

// Implement the logic to transition the plant to the next state
void DeadState::transitionToNext() {
}

DeadState::DeadState(GreenHousePlant * plant) : PlantState(plant) {
	DeadState::transitionToNext();
}
