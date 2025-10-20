#ifndef SENESCENCESTATE_H
#define SENESCENCESTATE_H
/**
 * @file SenescenceState.h
 * @brief This file contains the definition of the SenescenceState class.
 */

/**
 * @class SenescenceState
 * @brief Represents the plant being in the senescence state of its lifetime.
 */
class SenescenceState : Class_Diagram,_State_and_Prototype::PlantState {

public:

	/**
	 * @brief Handles the care actions specific to the senescence state.
	 */
	void handleCare();

	/**
	 * @brief Transitions the plant to the next state in its lifecycle.
	 */
	void transitionToNext();
};

#endif
