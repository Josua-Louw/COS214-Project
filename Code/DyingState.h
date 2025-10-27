#ifndef DYINGSTATE_H
#define DYINGSTATE_H

#include <thread>
#include <chrono>

#include "PlantState.h"
#include "GreenHousePlant.h"
#include "DeadState.h"

/**
 * @file DyingState.h
 * @brief Defines the DyingState class for representing a plant's dying phase.
 * @details This file contains the declaration of the DyingState class, which is part of the plant lifecycle state machine. It represents the stage where the plant is in decline and at risk of death, though recovery to a previous state may be possible with sufficient care.
 */

/**
 * @class DyingState
 * @brief Represents the dying state in a plant's lifecycle.
 * @details The DyingState class models the phase where the plant is in critical condition, with declining health and vitality. It inherits from PlantState, part of the plant lifecycle state machine. Care actions, such as intensive watering or fertilizing, may allow recovery to a previous state, while insufficient care leads to the dead state.
 * @note This stage is critical, as the plant’s survival depends on immediate and effective care.
 * @see PlantState, SeedState, SeedlingState, JuvenileState, MatureState, FloweringState, DeadState
 */
class DyingState : public PlantState {
    private:
    PlantState* previous;
public:

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the dying state to either a previous state (e.g., MatureState or FloweringState) if sufficient care is provided, or to the dead state if no care is provided. Transitioning back to the SenescenceState is not possible, as the plant is too old to recover to that state.
     * @note The next state is typically the DeadState, or a previous state such as MatureState or FloweringState, depending on care actions. Recovery to SenescenceState is not allowed due to the plant’s advanced age.
     * @return void
     * @see DeadState, SeedState, SeedlingState, JuvenileState, MatureState, FloweringState
     */
    void transitionToNext() override;

    DyingState(GreenHousePlant* plant, PlantState* previous);
};

#endif // DYINGSTATE_H