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
		plant_->applyCurrentCare();
		if (plant_->getSuccess()) {
			plant_->setState(new SeedlingState(plant_));
		} else if (plant_->getBusy()) {
			while (!plant_->getSuccess()) {
				timing::sleep_for(std::chrono::milliseconds(100));
			}
			plant_->setState(new SeedlingState(plant_));
		} else {

			plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seed));
		}
	}).detach();
}

