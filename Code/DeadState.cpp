#include "DeadState.h"
#include <iostream>

// Implement the logic to transition the plant to the next state
void DeadState::transitionToNext() {
	std::cout << "\033[1;32mDead start\033[0m" << std::endl;
}

DeadState::DeadState(GreenHousePlant * plant) : PlantState(plant) {
	DeadState::transitionToNext();
}
