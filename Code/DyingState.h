#ifndef DYINGSTATE_H
#define DYINGSTATE_H
/**
 * @file DyingState.h
 * @brief This file contains the definition of the DyingState class.
 */

/**
 * @class DyingState
 * @brief Represents the plant being in the dying state of its lifetime.
 */
class DyingState : Class_Diagram,_State_and_Prototype::PlantState {

public:

	/**
	 * @brief Handles the care actions specific to the dying state.
	 */
	void handleCare();

	/**
	 * @brief Transitions the plant to the next state in its lifecycle.
	 */
	void transitionToNext();
};

#endif
