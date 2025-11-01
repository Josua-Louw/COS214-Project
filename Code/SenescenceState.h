#ifndef SENESCENCESTATE_H
#define SENESCENCESTATE_H

#include <thread>
#include <chrono>

#include "PlantState.h"
#include "DyingState.h"

/**
 * @file SenescenceState.h
 * @brief Defines the SenescenceState class for representing a plant's senescence phase.
 * @details This file contains the declaration of the SenescenceState class, which is part of the plant lifecycle state machine. It represents the final stage where the plant undergoes senescence (aging) before transitioning to a dying state.
 */

/**
 * @class SenescenceState
 * @brief Represents the senescence state in a plant's lifecycle.
 * @details The SenescenceState class models the phase where a plant is aging and no longer actively growing. This is the final stage before the plant transitions to a dying state. It inherits from PlantState, part of the plant lifecycle state machine.
 * @note This is the end of the plant's active lifecycle, and most care actions are ineffective.
 * @see PlantState, DyingState
 */
class SenescenceState : public PlantState {
public:

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the senescence state to the dying state, marking the end of its lifecycle.
     * @note The next state is typically the DyingState.
     * @return void
     * @see DyingState
     */
    void transitionToNext() override;

    explicit SenescenceState(GreenHousePlant* plant);
};

#endif