#ifndef SEEDLING_STATE_H
#define SEEDLING_STATE_H

/**
* @file SeedlingState.h
* @brief This file contains the definition of the SeedlingState class.
*/

/**
* @class SeedlingState
* @brief Represents the plant being in the seedling state of its lifetime.
*/
class SeedlingState {
public:

    /**
    * @brief Handles the care actions specific to the seedling state.
    */
    void handleCare();

    /**
    * @brief Transitions the plant to the next state in its lifecycle.
    */
    void transitionToNext();
};

#endif // SEEDLING_STATE_H