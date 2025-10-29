#include "DyingState.h"

#include <utility>
#include "SeedState.h"
#include "SeedlingState.h"
#include "JuvenileState.h"
#include "MatureState.h"
#include "FloweringState.h"
#include "SenescenceState.h"

// If you added the timing shim, include it and replace sleeps accordingly.

DyingState::DyingState(GreenHousePlant* plant, std::string previousKind) : PlantState(plant), prevKind(std::move(previousKind)) {
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
            std::cout << "Test Dead" << std::endl;
            plant_->setState(new DeadState(plant_));
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));



        if (plant_->getWaterSuccess() && plant_->getFertilizingSuccess()) {
            std::cout << "Dying succeed " << plant_->getName() << std::endl;
            if (prevKind == "Seed") {
                plant_->setState(new SeedState(plant_));
            } else if (prevKind == "Seedling") {
                plant_->setState(new SeedlingState(plant_));
            } else if (prevKind == "Juvenile") {
                plant_->setState(new JuvenileState(plant_));
            } else if (prevKind == "Mature") {
                plant_->setState(new MatureState(plant_));
            } else if (prevKind == "Flowering") {
                plant_->setState(new FloweringState(plant_));
            } else if (prevKind == "Senescence") {
                plant_->setState(new SenescenceState(plant_));
            } else {
                plant_->setState(new DeadState(plant_));
            }
            std::cout << "Test Succeed" << std::endl;
            return;
        } else if (plant_->getWaterBusy() || plant_->getFertilizingBusy()) {
            while (!plant_->getWaterSuccess() || !plant_->getFertilizingSuccess()) {
                // timing::sleep_for(std::chrono::milliseconds(100));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Dying succeed " << plant_->getName() << std::endl;
            if (prevKind == "Seed") {
                plant_->setState(new SeedState(plant_));
            } else if (prevKind == "Seedling") {
                plant_->setState(new SeedlingState(plant_));
            } else if (prevKind == "Juvenile") {
                plant_->setState(new JuvenileState(plant_));
            } else if (prevKind == "Mature") {
                plant_->setState(new MatureState(plant_));
            } else if (prevKind == "Flowering") {
                plant_->setState(new FloweringState(plant_));
            } else if (prevKind == "Senescence") {
                plant_->setState(new SenescenceState(plant_));
            } else {
                plant_->setState(new DeadState(plant_));
            }
            std::cout << "Test Busy" << std::endl;
            return;
        } else {
            for (auto command : commands) {
                if (command)
                    command->setAbortStatus(true);
            }
            std::cout << "Dying fail " << plant_->getName() << std::endl;
            plant_->setState(new DeadState(plant_));
            std::cout << "Test Dead" << std::endl;
            return;
        }
    }).detach();
}
