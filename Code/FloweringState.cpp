#include "FloweringState.h"
#include "Timing.h"

// Implement the logic to transition the plant to the next state
void FloweringState::transitionToNext() {
	std::thread([this]() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 4);
		int randomNumber = dist(gen);
		timing::sleep_for(std::chrono::seconds(20));
			plant_->applyCurrentCare();
			if (plant_->getSuccess()) {
				if (randomNumber == 1) {
					plant_->setState(new SenescenceState(plant_));
				} else {
					plant_->setState(new MatureState(plant_));
				}
			} else if (plant_->getBusy()) {
				while (!plant_->getSuccess()) {
					timing::sleep_for(std::chrono::milliseconds(100));
				}
				for (auto command : commands) delete command;
				if (randomNumber == 1) {
					plant_->setState(new SenescenceState(plant_));
				} else {
					plant_->setState(new MatureState(plant_));
				}
			} else {
				for (auto command : commands) {
					command->setAbortStatus(true);
				}
				plant_->setState(new DyingState(plant_, DyingState::PrevKind::Flowering));
			}
		}).detach();
}

FloweringState::FloweringState(GreenHousePlant * plant) : PlantState(plant) {
	FloweringState::transitionToNext();
}
