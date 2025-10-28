#include "DyingState.h"
#include "SeedState.h"
#include "SeedlingState.h"
#include "JuvenileState.h"
#include "MatureState.h"
#include "FloweringState.h"
#include "SenescenceState.h"
#include "Timing.h"

// If you added the timing shim, include it and replace sleeps accordingly.
// #include "Timing.h"

DyingState::DyingState(GreenHousePlant* plant, PrevKind previousKind)
: PlantState(plant), prevKind(previousKind) {
    DyingState::transitionToNext();
}

void DyingState::transitionToNext() {
    std::thread([this]() {
        // timing::sleep_for(std::chrono::seconds(20));
        timing::sleep_for(std::chrono::seconds(20));

        std::vector<Command*> commands = plant_->applyCurrentCare();

        auto goPrevious = [this]() {
            switch (prevKind) {
                case PrevKind::Seed:        plant_->setState(new SeedState(plant_)); break;
                case PrevKind::Seedling:    plant_->setState(new SeedlingState(plant_)); break;
                case PrevKind::Juvenile:    plant_->setState(new JuvenileState(plant_)); break;
                case PrevKind::Mature:      plant_->setState(new MatureState(plant_)); break;
                case PrevKind::Flowering:   plant_->setState(new FloweringState(plant_)); break;
                default:                    plant_->setState(new DeadState(plant_)); break;
            }
        };

        if (plant_->getSuccess()) {
            for (auto command : commands) delete command;
            goPrevious();
        } else if (plant_->getBusy()) {
            while (!plant_->getSuccess()) {
                // timing::sleep_for(std::chrono::milliseconds(100));
                timing::sleep_for(std::chrono::milliseconds(100));
            }
            for (auto command : commands) delete command;
            goPrevious();
        } else {
            for (auto command : commands) {
                command->setAbortStatus(true);
            }
            plant_->setState(new DeadState(plant_));
        }
    }).detach();
}
