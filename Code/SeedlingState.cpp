 #include "SeedlingState.h"

#include <iostream>
#include <ostream>

 // Implement the logic to transition the plant to the next state
void SeedlingState::transitionToNext() {
    if (!plant_ || plant_->getIsAlive() == false) {
        return;
    }
    std::thread([this]() {
        std::cout << "\033[1;32mSeedling start\033[0m " << plant_->getName() << std::endl;
        std::vector<CommandPtr> commands = plant_->applyCurrentCare();
        if (commands.empty()) {
            plant_->setState(new DeadState(plant_));
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));

        if (plant_->getSuccess()) {
            std::cout << "Seedling success " << plant_->getName() << std::endl;
            plant_->setState(new JuvenileState(plant_));
        } else if (plant_->getBusy()) {
            while (!plant_->getSuccess()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Seedling success " << plant_->getName() << std::endl;
            plant_->setState(new JuvenileState(plant_));
        } else {
            for (auto command : commands) {
                if (command)
                    command->setAbortStatus(true);
            }
            std::cout << "Seedling fail " << plant_->getName() << std::endl;
            plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seedling));
        }
    }).detach();
}

SeedlingState::SeedlingState(GreenHousePlant * plant) : PlantState(plant) {
    SeedlingState::transitionToNext();
}
