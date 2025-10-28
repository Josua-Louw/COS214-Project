#include "JuvenileState.h"
#include "Timing.h"

// Implement the logic to transition the plant to the next state
void JuvenileState::transitionToNext() {
    std::thread([this]() {
        timing::sleep_for(std::chrono::seconds(20));
        plant_->applyCurrentCare();

        if (plant_->getSuccess()) {
            plant_->setState(new MatureState(plant_));
        } else if (plant_->getBusy()) {
            while (!plant_->getSuccess()) {
                timing::sleep_for(std::chrono::milliseconds(100));
            }
            plant_->setState(new MatureState(plant_));
        } else {
            plant_->setState(new DyingState(plant_, new JuvenileState(plant_)));
        }
    }).detach();
}

JuvenileState::JuvenileState(GreenHousePlant * plant) : PlantState(plant){
    JuvenileState::transitionToNext();
}
