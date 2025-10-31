#include "PlantState.h"

void PlantState::setPlantAlive(bool plantExist) {
    this->plantAlive.store(plantExist, std::memory_order_release);
}

bool PlantState::isAlive() const {
    return this->plantAlive.load(std::memory_order_acquire);
}


