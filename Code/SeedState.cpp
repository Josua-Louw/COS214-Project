#include "SeedState.h"

#include "DyingState.h"
#include "SeedlingState.h"

SeedState::SeedState(GreenHousePlant * plant) : PlantState(plant){
	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);
	SeedState::transitionToNext();
}

void SeedState::transitionToNext() {
	if (!plant_ || plant_->getIsActive() == false) {
		return;
	}
	std::thread([this]() {
		std::cout << "\033[1;32mSeed start\033[0m " << plant_->getName() << std::endl;
		std::vector<CommandPtr> commands = plant_->applyCurrentCare();
		if (commands.empty()) {
			if (!plant_->getIsActive()) {
				return;
			}
			plant_->setState(new DeadState(plant_));
			return;
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));
		if (plant_->getWaterSuccess() && plant_->getFertilizingSuccess()) {
			if (!plant_->getIsActive()) {
				return;
			}
			std::cout << "Seed success " << plant_->getName() << std::endl;
			plant_->setState(new SeedlingState(plant_));
			return;
		} else if (plant_->getWaterBusy() || plant_->getFertilizingBusy()) {
			if (!plant_->getIsActive()) {
				return;
			}
			while (!plant_->getWaterSuccess() || !plant_->getFertilizingSuccess()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			std::cout << "Seed success " << plant_->getName() << std::endl;
			plant_->setState(new SeedlingState(plant_));
			return;
		} else {
			for (auto command : commands) {
				if (command)
					command->setAbortStatus(true);
			}
			if (!plant_->getIsActive()) {
				return;
			}
			std::cout << "Seed fail " << plant_->getName() << std::endl;
			plant_->setState(new DyingState(plant_, "Seed"));
			return;
		}
	}).detach();
}

