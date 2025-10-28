#include "SeedState.h"

#include "DyingState.h"
#include "SeedlingState.h"

#include "Timing.h"

SeedState::SeedState(GreenHousePlant * plant) : PlantState(plant){
	SeedState::transitionToNext();
}

void SeedState::transitionToNext() {
	std::thread([this]() {
		timing::sleep_for(std::chrono::seconds(20));
		std::vector<Command*> commands = plant_->applyCurrentCare();
		if (plant_->getSuccess()) {
			for (auto command : commands) delete command;
			plant_->setState(new SeedlingState(plant_));
		} else if (plant_->getBusy()) {
			while (!plant_->getSuccess()) {
				timing::sleep_for(std::chrono::milliseconds(100));
			}
			for (auto command : commands) delete command;
			plant_->setState(new SeedlingState(plant_));
		} else {
			for (auto command : commands) {
				command->setAbortStatus(true);
			}
			plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seed));
		}
	}).detach();
}

