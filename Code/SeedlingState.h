#ifndef SEEDLING_STATE_H
#define SEEDLING_STATE_H

#include "PlantState.h"

/**
 * @file SeedlingState.h
 * @brief Defines the SeedlingState class for representing a plant's seedling phase.
 * @details This file contains the declaration of the SeedlingState class, which is part of the plant lifecycle state machine. It represents the stage where the plant is a young seedling, requiring careful nurturing to grow into the juvenile phase.
 */

/**
 * @class SeedlingState
 * @brief Represents the seedling state in a plant's lifecycle.
 * @details The SeedlingState class models the phase where the plant is a young seedling, recently germinated and vulnerable. It inherits from PlantState, part of the plant lifecycle state machine. Care actions in this state, such as watering and fertilizing, are critical for healthy growth and progression to the juvenile state.
 * @note This is an early, delicate stage in the plant's lifecycle.
 * @see PlantState, JuvenileState, DyingState
 */
class SeedlingState : public PlantState {
public:
    /**
     * @brief Handles care actions for a plant in the seedling state.
     * @details Performs care actions, such as watering and fertilizing, which are essential for supporting the seedling's growth and enabling it to advance to the juvenile state.
     * @note Proper care is critical in this delicate stage to ensure successful transition to the JuvenileState; insufficient care may lead to the DyingState.
     * @return void
     */
    void handleCare();

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the seedling state to the juvenile state if appropriate care has been provided. If care is insufficient, the plant transitions to the dying state.
     * @note The next state is typically the JuvenileState or, in case of inadequate care, the DyingState.
     * @return void
     * @see JuvenileState, DyingState
     */
    void transitionToNext();
};

#endif // SEEDLING_STATE_H