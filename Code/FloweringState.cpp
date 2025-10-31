#include "FloweringState.h"
#include <iostream>
#include <random>
#include "DeadState.h"
#include "MatureState.h"
#include "SenescenceState.h"
#include "DyingState.h"

void FloweringState::transitionToNext() {
    if (!plant_ || !plant_->getIsActive()) {
        return;
    }

    std::thread([this]() {
        GreenHousePlant* localPlant = plant_;
        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "\033[1;32mFlowering start\033[0m " << localPlant->getName() << std::endl;

        // Randomly decide next state (Mature or Senescence)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 3);
        int randomNumber = dist(gen);

        std::vector<CommandPtr> commands = localPlant->applyCurrentCare();
        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        if (commands.empty()) {
            localPlant->setState(new DeadState(localPlant));
            return;
        }

        // Wait 10 seconds with periodic checks
        for (int i = 0; i < 1000; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if (!localPlant || !localPlant->getIsActive()) {
                return;
            }
        }

        if (!localPlant || !localPlant->getIsActive()) {
            return;
        }

        // Success path
        if (localPlant->getWaterSuccess() && localPlant->getFertilizingSuccess()) {
            std::cout << "Flowering succeed " << localPlant->getName() << std::endl;

            if (!localPlant || !localPlant->getIsActive()) {
                return;
            }

            if (randomNumber == 1) {
                localPlant->setState(new SenescenceState(localPlant));
            } else {
                localPlant->setState(new MatureState(localPlant));
            }
            return;
        }

        // Wait while busy
        if (localPlant->getWaterBusy() || localPlant->getFertilizingBusy()) {
            while (localPlant->getIsActive() &&
                   (!localPlant->getWaterSuccess() || !localPlant->getFertilizingSuccess())) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            if (!localPlant || !localPlant->getIsActive()) {
                return;
            }

            std::cout << "Flowering succeed " << localPlant->getName() << std::endl;
            if (randomNumber == 1) {
                localPlant->setState(new SenescenceState(localPlant));
            } else {
                localPlant->setState(new MatureState(localPlant));
            }
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

        std::cout << "Flowering fail " << localPlant->getName() << std::endl;
        localPlant->setState(new DyingState(localPlant, "Flowering"));
    }).detach();
}

FloweringState::FloweringState(GreenHousePlant* plant) : PlantState(plant) {
    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    FloweringState::transitionToNext();
}
