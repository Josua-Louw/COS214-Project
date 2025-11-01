#include "DeadState.h"
#include "GreenHousePlant.h"
#include <iostream>
#include <thread>
#include <chrono>

void DeadState::transitionToNext() {
	if (!plant_ || !isAlive()) return;

	std::thread([this]() {
		GreenHousePlant* localPlant = plant_;
		if (!localPlant || !isAlive()) return;

		std::cout << "\033[1;31mDead start\033[0m " << localPlant->getName() << std::endl;

		// Short pause for consistency with other states
		for (int i = 0; i < 20; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			if (!isAlive() || !localPlant || !localPlant->getIsActive()) return;
		}

		if (isAlive() && localPlant->getIsActive()) {
			localPlant->deactivatePlant();
			std::cout << "\033[1;31mPlant deactivated:\033[0m "
					  << localPlant->getName() << std::endl;
		}
	}).detach();
}

DeadState::DeadState(GreenHousePlant* plant)
	: PlantState(plant) {
	if (!plant_ || !isAlive()) return;

	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);

	DeadState::transitionToNext();
}
