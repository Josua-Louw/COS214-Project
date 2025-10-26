#ifndef FLOWERINGSTATE_H
#define FLOWERINGSTATE_H

#include "PlantState.h"

/**
 * @file FloweringState.h
 * @brief Defines the FloweringState class for representing a plant's flowering phase.
 * @details This file contains the declaration of the FloweringState class, which is part of the plant lifecycle state machine. It represents the stage where the plant produces flowers, requiring specific care to support reproduction and determine the next lifecycle state.
 */

/**
 * @class FloweringState
 * @brief Represents the flowering state in a plant's lifecycle.
 * @details The FloweringState class models the phase where the plant is actively producing flowers, a critical stage for reproduction. It inherits from PlantState, part of the plant lifecycle state machine. Care actions, such as watering and fertilizing, are essential to sustain flowering and influence whether the plant returns to a mature state, progresses to senescence, or dies due to insufficient care.
 * @note This stage is pivotal for the plant’s reproductive success and subsequent lifecycle transitions.
 * @see PlantState, MatureState, SenescenceState, DyingState
 */
class FloweringState : public PlantState {
public:
    /**
     * @brief Handles care actions for a plant in the flowering state.
     * @details Performs care actions, such as watering and fertilizing, which are critical for supporting flower production and maintaining the plant’s health during this reproductive phase.
     * @note Proper care is essential to ensure successful flowering and to influence the plant’s next lifecycle state.
     * @return void
     */
    void handleCare();

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the flowering state to either the mature state, the senescence state, or the dying state if care is insufficient. The decision between mature and senescence states depends on the care strategy, which is not implemented in this method.
     * @note The next state is typically the MatureState, SenescenceState, or DyingState, based on care actions and strategy.
     * @return void
     * @see MatureState, SenescenceState, DyingState
     */
    void transitionToNext();
};

#endif // FLOWERINGSTATE_H