#ifndef DYINGSTATE_H
#define DYINGSTATE_H

#include <thread>
#include <chrono>
#include <memory>
#include "PlantState.h"
#include "GreenHousePlant.h"
#include "DeadState.h"

using CommandPtr = std::shared_ptr<Command>;

class SeedState;
class SeedlingState;
class JuvenileState;
class MatureState;
class FloweringState;
class SenescenceState;

class DyingState : public PlantState {
public:


private:
    std::string prevKind;

public:
    void transitionToNext() override;

    DyingState(GreenHousePlant* plant, std::string previousKind);

    void restorePreviousState(GreenHousePlant* plant);

    ~DyingState() {
        std::cout << "deleting DyingState" << std::endl;
    };
};

#endif // DYINGSTATE_H
