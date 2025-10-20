#ifndef PLANTSTATE_H
#define PLANTSTATE_H
/**
 * @file PlantState.h
 * @brief This file contains the definition of the PlantState class.
 */

/**
* @class PlantState
* @brief Abstract base class representing the state of a plant in its lifecycle.
*/
class PlantState {
public:
    /**
    * @brief Handles the care actions specific to the current state.
    */
    virtual void handleCare() = 0;

    /**
    * @brief Transitions the plant to the next state in its lifecycle.
    */
    virtual void transitionToNext() = 0;
};

#endif // PLANTSTATE_H