#include "SeedlingState.h"

#include <iostream>
#include <ostream>
#include "DyingState.h"
#include "JuvenileState.h"
#include "DeadState.h"

void SeedlingState::transitionToNext() {
    if (!plant_ || !isAlive() || !plant_->getIsActive()) {
        return;
    }

    std::thread([this]() {
        GreenHousePlant* localPlant = plant_;

        if (!localPlant || !isAlive() || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "\033[1;32mSeedling start\033[0m " << localPlant->getName() << std::endl;

        std::vector<CommandPtr> commands = localPlant->applyCurrentCare();

        if (!localPlant || !isAlive() || !localPlant->getIsActive()) {
            return;
        }

        if (commands.empty()) {
            localPlant->setState(new DeadState(localPlant));
            return;
        }

        // Sleep for 10 seconds but abort early if the plant dies
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            if (!localPlant || !isAlive() || !localPlant->getIsActive()) {
                return;
            }
        }

        if (!localPlant || !isAlive() || !localPlant->getIsActive()) {
            return;
        }

        // Success path
        if (localPlant->getWaterSuccess() && localPlant->getFertilizingSuccess()) {
            std::cout << "Seedling success " << localPlant->getName() << std::endl;
            localPlant->setState(new JuvenileState(localPlant));
            return;
        }

        // Wait if still busy
        if (localPlant->getWaterBusy() || localPlant->getFertilizingBusy()) {
            while (isAlive() && localPlant->getIsActive() &&
                   (!localPlant->getWaterSuccess() || !localPlant->getFertilizingSuccess())) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            if (!localPlant || !isAlive() || !localPlant->getIsActive()) {
                return;
            }

            std::cout << "Seedling success " << localPlant->getName() << std::endl;
            localPlant->setState(new JuvenileState(localPlant));
            return;
        }

        // Failure path
        for (auto& command : commands) {
            if (command)
                command->setAbortStatus(true);
        }

        if (!localPlant || !isAlive() || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "Seedling fail " << localPlant->getName() << std::endl;
        localPlant->setState(new DyingState(localPlant, "Seedling"));
    }).detach();
}

SeedlingState::SeedlingState(GreenHousePlant* plant)
    : PlantState(plant) {
    if (!plant_ || !isAlive()) return;

    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    SeedlingState::transitionToNext();
}
