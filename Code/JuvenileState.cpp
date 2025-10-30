#include "JuvenileState.h"

#include <iostream>
#include <ostream>

// Implement the logic to transition the plant to the next state
void JuvenileState::transitionToNext() {
    if (!plant_ || plant_->getIsActive() == false) {
        return;
    }
    std::thread([this]() {
        std::cout << "\033[1;32mJuvenile start\033[0m " << plant_->getName() << std::endl;
        std::vector<CommandPtr> commands = plant_->applyCurrentCare();
        if (commands.empty()) {
            if (!plant_->getIsActive()) {
                return;
            }
            plant_->setState(new DeadState(plant_));
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));


        if (plant_->getWaterSuccess() && plant_->getFertilizingSuccess()) {
            if (!plant_->getIsActive()) {
                return;
            }
            std::cout << "Juvenile success " << plant_->getName() << std::endl;
            plant_->setState(new MatureState(plant_));
            return;
        } else if (plant_->getWaterBusy() || plant_->getFertilizingBusy()) {
            if (!plant_->getIsActive()) {
                return;
            }
            while (!plant_->getWaterSuccess() || !plant_->getFertilizingSuccess()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Juvenile success " << plant_->getName() << std::endl;
            plant_->setState(new MatureState(plant_));
            return;
        } else {
            for (auto command : commands) {
                if (command)
                    command->setAbortStatus(true);
            }
            if (!plant_->getIsActive()) {
                return;
            }
            std::cout << "Juvenile fail " << plant_->getName() << std::endl;
            plant_->setState(new DyingState(plant_, "Juvenile"));
            return;
        }
    }).detach();
}

JuvenileState::JuvenileState(GreenHousePlant * plant) : PlantState(plant){
    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    JuvenileState::transitionToNext();
}
