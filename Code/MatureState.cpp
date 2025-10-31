#include "MatureState.h"
#include <iostream>
#include "DyingState.h"
#include "DeadState.h"
#include "FloweringState.h"

void MatureState::transitionToNext() {
    if (!plant_ || !plant_->getIsActive()) {
        return;
    }

    std::thread([this]() {
        GreenHousePlant* localPlant = plant_;
        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "\033[1;32mMature start\033[0m " << localPlant->getName() << std::endl;

        std::vector<CommandPtr> commands = localPlant->applyCurrentCare();
        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        if (commands.empty()) {
            localPlant->setState(new DeadState(localPlant));
            return;
        }

        // Sleep for 10 seconds, but check for life every 100ms
        for (int i = 0; i < 100; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (!localPlant || !localPlant->getIsActive()) {
                return;
            }
        }

        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        // Success path
        if (localPlant->getWaterSuccess() && localPlant->getFertilizingSuccess()) {
            std::cout << "Mature succeed " << localPlant->getName() << std::endl;
            localPlant->setState(new FloweringState(localPlant));
            return;
        }

        // Wait for completion if busy
        if (localPlant->getWaterBusy() || localPlant->getFertilizingBusy()) {
            while (localPlant->getIsActive() &&
                   (!localPlant->getWaterSuccess() || !localPlant->getFertilizingSuccess())) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            if (!localPlant || !localPlant->getIsActive()) {
                return;
            }

            std::cout << "Mature succeed " << localPlant->getName() << std::endl;
            localPlant->setState(new FloweringState(localPlant));
            return;
        }

        // Failure path
        for (auto& command : commands) {
            if (command)
                command->setAbortStatus(true);
        }

        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "Mature fail " << localPlant->getName() << std::endl;
        localPlant->setState(new DyingState(localPlant, "Mature"));
    }).detach();
}

MatureState::MatureState(GreenHousePlant* plant) : PlantState(plant) {
    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    MatureState::transitionToNext();
}
