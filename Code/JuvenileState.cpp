#include "JuvenileState.h"

#include <iostream>
#include <ostream>

// Implement the logic to transition the plant to the next state
void JuvenileState::transitionToNext() {
    std::thread([this]() {
        std::cout << "\033[1;32mJuvenile start\033[0m" << std::endl;
        std::vector<Command*> commands = plant_->applyCurrentCare();
        std::this_thread::sleep_for(std::chrono::seconds(10));


        if (plant_->getSuccess()) {
            std::cout << "Juvenile success" << std::endl;
            plant_->setState(new MatureState(plant_));
        } else if (plant_->getBusy()) {
            std::cout << "Juvenile pending success" << std::endl;
            while (!plant_->getSuccess()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Juvenile success" << std::endl;
            plant_->setState(new MatureState(plant_));
        } else {
            for (auto command : commands) {
                if (command)
                    command->setAbortStatus(true);
            }
            std::cout << "Juvenile fail" << std::endl;
            plant_->setState(new DyingState(plant_, DyingState::PrevKind::Juvenile));
        }
    }).detach();
}

JuvenileState::JuvenileState(GreenHousePlant * plant) : PlantState(plant){
    JuvenileState::transitionToNext();
}
