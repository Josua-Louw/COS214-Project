#include "FloweringState.h"

// Implement the logic to transition the plant to the next state
void FloweringState::transitionToNext() {
	std::thread([this]() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 4);
		int randomNumber = dist(gen);
			std::this_thread::sleep_for(std::chrono::seconds(20));
			plant_->applyCurrentCare();
			if (plant_->getSuccess()) {
				if (randomNumber == 1) {
					plant_->setState(new SenescenceState(plant_));
				} else {
					plant_->setState(new MatureState(plant_));
				}
			} else if (plant_->getBusy()) {
				while (!plant_->getSuccess()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
				if (randomNumber == 1) {
					plant_->setState(new SenescenceState(plant_));
				} else {
					plant_->setState(new MatureState(plant_));
				}
			} else {
				plant_->setState(new DyingState(plant_,new FloweringState(plant_)));
			}
		}).detach();
}

FloweringState::FloweringState(GreenHousePlant * plant) : PlantState(plant) {
	FloweringState::transitionToNext();
}
