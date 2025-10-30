#include "DeadState.h"
#include <iostream>

#include "GreenHousePlant.h"

// Implement the logic to transition the plant to the next state
void DeadState::transitionToNext() {
	if (plant_ == nullptr) {
		return;
	}
	std::cout << "\033[1;32mDead start\033[0m " << plant_->getName() << std::endl;
	if (!plant_ || plant_->getIsActive()) {
		plant_->deactivatePlant();
	};
}

DeadState::DeadState(GreenHousePlant * plant) : PlantState(plant) {
	if (plant_ == nullptr) {
		return;
	}
	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);
	DeadState::transitionToNext();
}
