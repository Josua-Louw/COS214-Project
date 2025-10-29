#ifndef MATURESTATE_H
#define MATURESTATE_H

#include <thread>
#include <chrono>
#include <memory>

#include "PlantState.h"
#include "FloweringState.h"
#include "DyingState.h"

using CommandPtr = std::shared_ptr<Command>;

/**
 * @file MatureState.h
 * @brief Defines the MatureState class for representing a plant's mature phase.
 * @details This file contains the declaration of the MatureState class, which is part of the plant lifecycle state machine. It represents the stage where the plant is fully developed and capable of reproduction, requiring ongoing care to progress to flowering.
 */

/**
 * @class MatureState
 * @brief Represents the mature state in a plant's lifecycle.
 * @details The MatureState class models the phase where the plant is fully grown and at its peak vigor, ready to transition to the flowering state with proper care. It inherits from PlantState, part of the plant lifecycle state machine. Care actions, such as watering and fertilizing, are essential to maintain health and enable reproduction.
 * @note This stage represents the plant’s prime, where it is most robust before entering reproductive phases.
 * @see PlantState, FloweringState, DyingState
 */
class MatureState : public PlantState {
public:

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the mature state to the flowering state if appropriate care has been provided. If care is insufficient, the plant transitions to the dying state.
     * @note The next state is typically the FloweringState or, in case of inadequate care, the DyingState.
     * @return void
     * @see FloweringState, DyingState
     */
    void transitionToNext() override;

    explicit MatureState(GreenHousePlant* plant);
};

#endif // MATURESTATE_H