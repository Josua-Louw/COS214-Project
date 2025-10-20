#ifndef SEEDSTATE_H
#define SEEDSTATE_H

/**
* @file SeedState.h
* @brief This file contains the definition of the SeedState class.
*/

/**
* @class SeedState
* @brief Represents the plant being in the seed state of its lifetime.
*/
class SeedState : Class_Diagram,_State_and_Prototype::PlantState {

public:

	/**
	* @brief Handles the care actions specific to the seed state.
	*/
	void handleCare();

	/**
	* @brief Transitions the plant to the next state in its lifecycle.
	*/
	void transitionToNext();
};

#endif
