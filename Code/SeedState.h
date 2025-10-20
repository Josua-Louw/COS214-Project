#ifndef SEEDSTATE_H
#define SEEDSTATE_H

#include "PlantState.h"

/**
 * @file SeedState.h
 * @brief Defines the SeedState class for representing a plant's seed phase.
 * @details This file contains the declaration of the SeedState class, which is part of the plant lifecycle state machine. It represents the initial stage where the plant exists as a seed, requiring specific care actions to germinate.
 */

/**
 * @class SeedState
 * @brief Represents the seed state in a plant's lifecycle.
 * @details The SeedState class models the initial phase where the plant is a seed, preparing to germinate. It inherits from PlantState, part of the plant lifecycle state machine. Care actions in this state, such as watering and fertilizing, are critical for successful germination and progression to the seedling state.
 * @note This is the starting point of the plant's lifecycle.
 * @see PlantState, SeedlingState, DyingState
 */
class SeedState : public PlantState {
public:
	/**
	 * @brief Handles care actions for a plant in the seed state.
	 * @details Performs care actions, such as watering and fertilizing, which are essential for triggering germination and enabling the plant to advance to the seedling state.
	 * @note Proper care is required for the seed to successfully transition to the SeedlingState; insufficient care may lead to the DyingState.
	 * @return void
	 */
	void handleCare();

	/**
	 * @brief Transitions the plant to the next state in its lifecycle.
	 * @details Moves the plant from the seed state to the seedling state if appropriate care has been provided. If care is insufficient, the plant transitions to the dying state.
	 * @note The next state is typically the SeedlingState or, in case of inadequate care, the DyingState.
	 * @return void
	 * @see SeedlingState, DyingState
	 */
	void transitionToNext();
};

#endif