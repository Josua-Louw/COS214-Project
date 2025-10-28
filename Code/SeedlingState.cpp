 #include "SeedlingState.h"

#include <iostream>
#include <ostream>

 // Implement the logic to transition the plant to the next state
void SeedlingState::transitionToNext() {
    std::thread([this]() {
        std::cout << "\033[1;32mSeedling start\033[0m" << std::endl;
        std::vector<Command*> commands = plant_->applyCurrentCare();
        std::this_thread::sleep_for(std::chrono::seconds(10));

        if (plant_->getSuccess()) {
            std::cout << "Seedling success" << std::endl;
            plant_->setState(new JuvenileState(plant_));
        } else if (plant_->getBusy()) {
            std::cout << "Seedling pending success" << std::endl;
            while (!plant_->getSuccess()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Seedling success" << std::endl;
            plant_->setState(new JuvenileState(plant_));
        } else {
            for (auto command : commands) {
                if (command)
                    command->setAbortStatus(true);
            }
            std::cout << "Seedling fail" << std::endl;
            plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seedling));
        }
    }).detach();
}

SeedlingState::SeedlingState(GreenHousePlant * plant) : PlantState(plant) {
    SeedlingState::transitionToNext();
}
