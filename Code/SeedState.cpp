#include "SeedState.h"

#include "DyingState.h"
#include "SeedlingState.h"

SeedState::SeedState(GreenHousePlant * plant) : PlantState(plant){
	SeedState::transitionToNext();
}

void SeedState::transitionToNext() {
	if (!plant_ || plant_->getIsAlive() == false) {
		return;
	}
	std::thread([this]() {
		std::cout << "\033[1;32mSeed start\033[0m " << plant_->getName() << std::endl;
		std::vector<CommandPtr> commands = plant_->applyCurrentCare();
		if (commands.empty()) {
			plant_->setState(new DeadState(plant_));
		}
		std::this_thread::sleep_for(std::chrono::seconds(10));

		if (plant_->getSuccess()) {
			std::cout << "Seed success " << plant_->getName() << std::endl;
			plant_->setState(new SeedlingState(plant_));
		} else if (plant_->getBusy()) {
			while (!plant_->getSuccess()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			std::cout << "Seed success " << plant_->getName() << std::endl;
			plant_->setState(new SeedlingState(plant_));
		} else {
			for (auto command : commands) {
				if (command)
					command->setAbortStatus(true);
			}
			std::cout << "Seed fail " << plant_->getName() << std::endl;
			plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seed));
		}
	}).detach();
}

