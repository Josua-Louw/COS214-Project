#include "SenescenceState.h"
#include "DeadState.h"
#include <iostream>
#include <thread>

void SenescenceState::transitionToNext() {
	if (!plant_ || !plant_->getIsActive()) {
		return;
	}

	std::thread([this]() {
		GreenHousePlant* localPlant = plant_;
		if (!localPlant || !localPlant->getIsActive()) {
			return;
		}

		std::cout << "\033[1;32mSenescence start\033[0m " << localPlant->getName() << std::endl;

		// Sleep with periodic active checks
		for (int i = 0; i < 100; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			if (!localPlant || !localPlant->getIsActive()) {
				return;
			}
		}

		if (!localPlant || !localPlant->getIsActive()) {
			return;
		}

		std::cout << "Senescence fail " << localPlant->getName() << std::endl;
		localPlant->setState(new DeadState(localPlant));
	}).detach();
}

SenescenceState::SenescenceState(GreenHousePlant* plant) : PlantState(plant) {
	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);
	SenescenceState::transitionToNext();
}
