#ifndef JUVENILESTATE_H
#define JUVENILESTATE_H

#include "PlantState.h"
/**
 * @file JuvenileState.h
 * @brief This file contains the definition of the JuvenileState class.
 */

/**
* @class JuvenileState
* @brief Represents the plant being in the juvenile state of its lifetime.
*/
class JuvenileState : public PlantState {

public:

    /**
    * @brief Handles the care actions specific to the juvenile state.
    */
    void handleCare();

    /**
    * @brief Transitions the plant to the next state in its lifecycle.
    */
    void transitionToNext();

};

#endif // JUVENILESTATE_H