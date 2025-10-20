#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"
/**
 * @file MatureState.h
 * @brief This file contains the definition of the MatureState class.
 */

/**
* @class MatureState
* @brief Represents the plant being in the mature state of its lifetime.
*/
class MatureState : public PlantState {
public:

    /**
    * @brief Handles the care actions specific to the mature state.
    */
    void handleCare();

    /**
    * @brief Transitions the plant to the next state in its lifecycle.
    */
    void transitionToNext();
};

#endif // MATURESTATE_H