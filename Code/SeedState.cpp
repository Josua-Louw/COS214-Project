#include "SeedState.h"
#include "DyingState.h"
#include "SeedlingState.h"

SeedState::SeedState(GreenHousePlant* plant)
    : PlantState(plant) {
    if (!plant_ || !doesPlantExist()) return;

    plant_->setWaterSuccess(false);
    plant_->setFertilizingSuccess(false);
    plant_->setWaterBusy(false);
    plant_->setFertilizingBusy(false);
    SeedState::transitionToNext();
}

void SeedState::transitionToNext() {
    if (!plant_ || !doesPlantExist() || !plant_->getIsActive()) {
        return;
    }

    std::thread([this]() {
        GreenHousePlant* localPlant = plant_;  // capture once safely

        if (!localPlant || !doesPlantExist() || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "\033[1;32mSeed start\033[0m " << localPlant->getName() << std::endl;

        std::vector<CommandPtr> commands = localPlant->applyCurrentCare();

        if (!localPlant || !doesPlantExist() || !localPlant->getIsActive()) {
            return;
        }

        if (commands.empty()) {
            localPlant->setState(new DeadState(localPlant));
            return;
        }

        // Simulate growth duration
        for (int i = 0; i < 1000; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if (!localPlant || !doesPlantExist() || !localPlant->getIsActive()) {
                return;
            }
        }

        if (!localPlant || !doesPlantExist() || !localPlant->getIsActive()) {
            return;
        }

        // Success paths
        if (localPlant->getWaterSuccess() && localPlant->getFertilizingSuccess()) {
            std::cout << "Seed success " << localPlant->getName() << std::endl;
            localPlant->setState(new SeedlingState(localPlant));
            return;
        }

        // Wait for completion if busy
        if (localPlant->getWaterBusy() || localPlant->getFertilizingBusy()) {
            while (doesPlantExist() && localPlant->getIsActive() &&
                   (!localPlant->getWaterSuccess() || !localPlant->getFertilizingSuccess())) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            if (!localPlant || !doesPlantExist() || !localPlant->getIsActive()) {
                return;
            }

            std::cout << "Seed success " << localPlant->getName() << std::endl;
            localPlant->setState(new SeedlingState(localPlant));
            return;
        }

        // Failure path
        for (auto& command : commands) {
            if (command)
                command->setAbortStatus(true);
        }

        if (!localPlant || !doesPlantExist() || !localPlant->getIsActive()) {
            return;
        }

        std::cout << "Seed fail " << localPlant->getName() << std::endl;
        localPlant->setState(new DyingState(localPlant, "Seed"));
    }).detach();
}
