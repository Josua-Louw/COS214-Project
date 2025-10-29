#include "FloweringState.h"
#include <iostream>

// Implement the logic to transition the plant to the next state
void FloweringState::transitionToNext() {
	if (!plant_ || plant_->getIsAlive() == false) {
		return;
	}
	std::thread([this]() {
		std::cout << "\033[1;32mFlowering start\033[0m " << plant_->getName() << std::endl;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 2);
		int randomNumber = dist(gen);
		std::vector<CommandPtr> commands = plant_->applyCurrentCare();
		if (commands.empty()) {
			plant_->setState(new DeadState(plant_));
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));

			if (plant_->getWaterSuccess() && plant_->getFertilizingSuccess()) {
				std::cout << "Flowering succeed " << plant_->getName() << std::endl;
				if (randomNumber == 1) {
					plant_->setState(new SenescenceState(plant_));
				} else {
					plant_->setState(new MatureState(plant_));
				}
			} else if (plant_->getWaterBusy() || plant_->getFertilizingBusy()) {
				while (!plant_->getWaterSuccess() || !plant_->getFertilizingSuccess()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				std::cout << "Flowering succeed " << plant_->getName() << std::endl;
				if (randomNumber == 1) {
					plant_->setState(new SenescenceState(plant_));
				} else {
					plant_->setState(new MatureState(plant_));
				}
			} else {
				for (auto command : commands) {
					if (command)
						command->setAbortStatus(true);
				}
				std::cout << "Flowering fail " << plant_->getName() << std::endl;
				plant_->setState(new DyingState(plant_, "Flowering"));
			}
		}).detach();
}

FloweringState::FloweringState(GreenHousePlant * plant) : PlantState(plant) {
	plant_->setWaterSuccess(false);
	plant_->setFertilizingSuccess(false);
	plant_->setWaterBusy(false);
	plant_->setFertilizingBusy(false);
	FloweringState::transitionToNext();
}
