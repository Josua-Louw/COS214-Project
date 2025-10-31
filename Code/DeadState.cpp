#include "DeadState.h"
#include "GreenHousePlant.h"
#include <iostream>
#include <thread>
#include <chrono>

void DeadState::transitionToNext() {
	if (!plant_) return;

	std::thread([this]() {
		GreenHousePlant* localPlant = plant_;
		if (!localPlant) return;

		std::cout << "\033[1;31mDead start\033[0m " << localPlant->getName() << std::endl;

		// Small pause before final shutdown (optional, for consistency)
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

		if (localPlant->getIsActive()) {
			localPlant->deactivatePlant();
			std::cout << "\033[1;31mPlant deactivated:\033[0m "
					  << localPlant->getName() << std::endl;
		}
	}).detach();
}

DeadState::DeadState(GreenHousePlant* plant) : PlantState(plant) {
	if (!plant_) return;

	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);

	DeadState::transitionToNext();
}
