#include "JuvenileState.h"
#include "Timing.h"

// Implement the logic to transition the plant to the next state
void JuvenileState::transitionToNext() {
    std::thread([this]() {
        timing::sleep_for(std::chrono::seconds(20));
        std::vector<Command*> commands = plant_->applyCurrentCare();

        if (plant_->getSuccess()) {
            for (auto command : commands) delete command;
            plant_->setState(new MatureState(plant_));
        } else if (plant_->getBusy()) {
            while (!plant_->getSuccess()) {
                timing::sleep_for(std::chrono::milliseconds(100));
            }
            for (auto command : commands) delete command;
            plant_->setState(new MatureState(plant_));
        } else {
            for (auto command : commands) {
                command->setAbortStatus(true);
            }
            plant_->setState(new DyingState(plant_, DyingState::PrevKind::Juvenile));
        }
    }).detach();
}

JuvenileState::JuvenileState(GreenHousePlant * plant) : PlantState(plant){
    JuvenileState::transitionToNext();
}
