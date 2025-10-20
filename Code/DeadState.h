#ifndef DEADSTATE_H
#define DEADSTATE_H
/**
 * @file DeadState.h
 * @brief This file contains the definition of the DeadState class.
 */

/**
 * @class DeadState
 * @brief Represents the plant being in the dead state of its lifetime.
 */
class DeadState : Class_Diagram,_State_and_Prototype::PlantState {

public:

	/**
	 * @brief Handles the care actions specific to the dead state.
	 */
	void handleCare();

	/**
	 * @brief Transitions the plant to the next state in its lifecycle.
	 */
	void transitionToNext();
};

#endif
