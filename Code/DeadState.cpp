#include "DeadState.h"
#include <iostream>

#include "GreenHousePlant.h"

// Implement the logic to transition the plant to the next state
void DeadState::transitionToNext() {
	std::cout << "\033[1;32mDead start\033[0m " << plant_->getName() << std::endl;
	if (plant_->getIsAlive()) {
		plant_->killPlant();
	};
}

DeadState::DeadState(GreenHousePlant * plant) : PlantState(plant) {
	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);
	DeadState::transitionToNext();
}
