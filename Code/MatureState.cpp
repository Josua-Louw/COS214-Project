#include "MatureState.h"
#include "Timing.h"

// Implement the logic to transition the plant to the next state
void MatureState::transitionToNext() {
    std::thread([this]() {
        timing::sleep_for(std::chrono::seconds(20));
        plant_->applyCurrentCare();

       if (plant_->getSuccess()) {
           plant_->setState(new FloweringState(plant_));
       } else if (plant_->getBusy()) {
           while (!plant_->getSuccess()) {
               timing::sleep_for(std::chrono::milliseconds(100));
           }
           for (auto command : commands) delete command;
           plant_->setState(new FloweringState(plant_));
       } else {
           for (auto command : commands) {
               command->setAbortStatus(true);
           }
           plant_->setState(new DyingState(plant_, DyingState::PrevKind::Mature));
       }
   }).detach();
}

MatureState::MatureState(GreenHousePlant * plant) : PlantState(plant) {
    MatureState::transitionToNext();
}
