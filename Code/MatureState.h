#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"

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
     * @brief Handles care actions for a plant in the mature state.
     * @details Performs care actions, such as watering and fertilizing, which are critical for maintaining the plant’s health and enabling it to advance to the flowering state.
     * @note Proper care is essential to ensure the plant remains healthy and can transition to the FloweringState; insufficient care may lead to the DyingState.
     * @return void
     */
    void handleCare();

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the mature state to the flowering state if appropriate care has been provided. If care is insufficient, the plant transitions to the dying state.
     * @note The next state is typically the FloweringState or, in case of inadequate care, the DyingState.
     * @return void
     * @see FloweringState, DyingState
     */
    void transitionToNext();
};

#endif // MATURESTATE_H