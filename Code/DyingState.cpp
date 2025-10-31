#include "DyingState.h"
#include "SeedState.h"
#include "SeedlingState.h"
#include "JuvenileState.h"
#include "MatureState.h"
#include "FloweringState.h"
#include "SenescenceState.h"
#include "DeadState.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <utility>

DyingState::DyingState(GreenHousePlant* plant, std::string previousKind)
    : PlantState(plant), prevKind(std::move(previousKind)) {
    if (!plant_) return;

    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);

    DyingState::transitionToNext();
}

void DyingState::transitionToNext() {
    if (!plant_ || !plant_->getIsActive()) {
        return;
    }

    std::thread([this]() {
        GreenHousePlant* localPlant = plant_;
        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "\033[1;32mDying start\033[0m " << localPlant->getName() << std::endl;
        std::vector<CommandPtr> commands = localPlant->applyCurrentCare();

        if (commands.empty()) {
            if (!localPlant || !localPlant->getIsActive()) return;
            localPlant->setState(new DeadState(localPlant));
            return;
        }

        // Wait 10 seconds with periodic active checks
        for (int i = 0; i < 100; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (!localPlant || !localPlant->getIsActive()) return;
        }

        if (!localPlant || !localPlant->getIsActive()) return;

        if (localPlant->getWaterSuccess() && localPlant->getFertilizingSuccess()) {
            std::cout << "Dying succeed " << localPlant->getName() << std::endl;
            restorePreviousState(localPlant);
            return;
        }

        if (localPlant->getWaterBusy() || localPlant->getFertilizingBusy()) {
            while (!localPlant->getWaterSuccess() || !localPlant->getFertilizingSuccess()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                if (!localPlant || !localPlant->getIsActive()) return;
            }
            std::cout << "Dying succeed " << localPlant->getName() << std::endl;
            restorePreviousState(localPlant);
            return;
        }

        for (auto& command : commands) {
            if (command) command->setAbortStatus(true);
        }

        if (!localPlant || !localPlant->getIsActive()) return;

        std::cout << "Dying fail " << localPlant->getName() << std::endl;
        localPlant->setState(new DeadState(localPlant));
    }).detach();
}

void DyingState::restorePreviousState(GreenHousePlant* plant) {
    if (!plant || !plant->getIsActive()) return;

    if (prevKind == "Seed") {
        plant->setState(new SeedState(plant));
    } else if (prevKind == "Seedling") {
        plant->setState(new SeedlingState(plant));
    } else if (prevKind == "Juvenile") {
        plant->setState(new JuvenileState(plant));
    } else if (prevKind == "Mature") {
        plant->setState(new MatureState(plant));
    } else if (prevKind == "Flowering") {
        plant->setState(new FloweringState(plant));
    } else if (prevKind == "Senescence") {
        plant->setState(new SenescenceState(plant));
    } else {
        plant->setState(new DeadState(plant));
    }
}
