#ifndef DYINGSTATE_H
#define DYINGSTATE_H

#include <thread>
#include <chrono>
#include "PlantState.h"
#include "GreenHousePlant.h"
#include "DeadState.h"

class SeedState;
class SeedlingState;
class JuvenileState;
class MatureState;
class FloweringState;
class SenescenceState;

class DyingState : public PlantState {
public:
    //What state should we revert to, if recovery succeeds?
    enum class PrevKind {
        Seed,
        Seedling,
        Juvenile,
        Mature,
        Flowering
    };

private:
    PrevKind prevKind;

public:
    void transitionToNext() override;

    DyingState(GreenHousePlant* plant, PrevKind previousKind);
};

#endif // DYINGSTATE_H
