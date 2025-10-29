#include "DyingState.h"
#include "SeedState.h"
#include "SeedlingState.h"
#include "JuvenileState.h"
#include "MatureState.h"
#include "FloweringState.h"
#include "SenescenceState.h"

// If you added the timing shim, include it and replace sleeps accordingly.

DyingState::DyingState(GreenHousePlant* plant, PrevKind previousKind) : PlantState(plant), prevKind(previousKind) {
    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    DyingState::transitionToNext();
}

void DyingState::transitionToNext() {
    if (!plant_ || plant_->getIsAlive() == false) {
        return;
    }
    std::thread([this]() {
        std::cout << "\033[1;32mDying start\033[0m " << plant_->getName() << std::endl;
        std::vector<CommandPtr> commands = plant_->applyCurrentCare();
        if (commands.empty()) {
            plant_->setState(new DeadState(plant_));
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));



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
            std::cout << "Dying succeed " << plant_->getName() << std::endl;
            goPrevious();
        } else if (plant_->getBusy()) {
            while (!plant_->getSuccess()) {
                // timing::sleep_for(std::chrono::milliseconds(100));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Dying succeed " << plant_->getName() << std::endl;
            goPrevious();
        } else {
            for (auto command : commands) {
                if (command)
                    command->setAbortStatus(true);
            }
            std::cout << "Dying fail " << plant_->getName() << std::endl;
            plant_->setState(new DeadState(plant_));
        }
    }).detach();
}
