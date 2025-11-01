#ifndef DEADSTATE_H
#define DEADSTATE_H

#include "PlantState.h"

/**
 * @file DeadState.h
 * @brief Defines the DeadState class for representing a plant's dead phase.
 * @details This file contains the declaration of the DeadState class, which is part of the plant lifecycle state machine. It represents the terminal stage where the plant is no longer alive and cannot be revived.
 */

/**
 * @class DeadState
 * @brief Represents the dead state in a plant's lifecycle.
 * @details The DeadState class models the final phase where the plant has died and all biological functions have ceased. It inherits from PlantState, part of the plant lifecycle state machine. No care actions or transitions are effective in this state, as the plant is permanently non-viable.
 * @note This is the terminal state of the plant’s lifecycle, with no possibility of recovery.
 * @see PlantState, DyingState
 */
class DeadState : public PlantState {
public:

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details This method is stubbed and performs no operations, as there is no next state beyond the dead state in the plant’s lifecycle.
     * @note This method is intentionally empty, as the dead state is terminal.
     * @return void
     */
    void transitionToNext() override;

    explicit DeadState(GreenHousePlant* plant);

    ~DeadState() {
        std::cout << "deleting DeadState" << std::endl;
    };
};

#endif // DEADSTATE_H