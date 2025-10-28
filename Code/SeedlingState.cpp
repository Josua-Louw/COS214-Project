#include "SeedlingState.h"
#include "Timing.h"

// Implement the logic to transition the plant to the next state
void SeedlingState::transitionToNext() {
    std::thread([this]() {
        timing::sleep_for(std::chrono::seconds(20));
        plant_->applyCurrentCare();

        if (plant_->getSuccess()) {
            plant_->setState(new JuvenileState(plant_));
        } else if (plant_->getBusy()) {
            while (!plant_->getSuccess()) {
                timing::sleep_for(std::chrono::milliseconds(100));
            }
            plant_->setState(new JuvenileState(plant_));
        } else {
            plant_->setState(new DyingState(plant_, DyingState::PrevKind::Seedling));
        }
    }).detach();
}

SeedlingState::SeedlingState(GreenHousePlant * plant) : PlantState(plant) {
    SeedlingState::transitionToNext();
}
