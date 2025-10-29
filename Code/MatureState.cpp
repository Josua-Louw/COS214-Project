#include "MatureState.h"
#include <iostream>

// Implement the logic to transition the plant to the next state
void MatureState::transitionToNext() {
    if (!plant_ || plant_->getIsAlive() == false) {
        return;
    }
    std::thread([this]() {
        std::cout << "\033[1;32mMature start\033[0m " << plant_->getName() << std::endl;
        std::vector<CommandPtr> commands = plant_->applyCurrentCare();
        if (commands.empty()) {
            plant_->setState(new DeadState(plant_));
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));


       if (plant_->getWaterSuccess() && plant_->getFertilizingSuccess()) {
           std::cout << "Mature succeed " << plant_->getName() << std::endl;
           plant_->setState(new FloweringState(plant_));
       } else if (plant_->getWaterBusy() || plant_->getFertilizingBusy()) {
           while (!plant_->getWaterSuccess() || !plant_->getFertilizingSuccess()) {
               std::this_thread::sleep_for(std::chrono::milliseconds(100));
           }
           std::cout << "Mature succeed " << plant_->getName() << std::endl;
           plant_->setState(new FloweringState(plant_));
       } else {
           for (auto command : commands) {
               if (command)
                command->setAbortStatus(true);
           }
           std::cout << "Mature fail " << plant_->getName() << std::endl;
           plant_->setState(new DyingState(plant_, "Mature"));
       }
   }).detach();
}

MatureState::MatureState(GreenHousePlant * plant) : PlantState(plant) {
    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    MatureState::transitionToNext();
}
