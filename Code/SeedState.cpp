#include "SeedState.h"

#include "DyingState.h"
#include "SeedlingState.h"

SeedState::SeedState(GreenHousePlant * plant) : PlantState(plant){
	std::cout << "Jou moer" << std::endl;
	SeedState::transitionToNext();
}

void SeedState::transitionToNext() {
	std::cout << "Test1" << std::endl;
	std::thread([this]() {
		std::this_thread::sleep_for(std::chrono::seconds(20));
		std::vector<Command*> commands = plant_->applyCurrentCare();
		if (plant_->getSuccess()) {
			std::cout << "Test1" << std::endl;
			plant_->setState(new SeedlingState(plant_));
		} else if (plant_->getBusy()) {
			while (!plant_->getSuccess()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			std::cout << "Test1" << std::endl;
			plant_->setState(new SeedlingState(plant_));
		} else {
			for (auto command : commands) {
				if (command)
					command->setAbortStatus(true);
			}
			plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seed));
		}
	}).detach();
}

