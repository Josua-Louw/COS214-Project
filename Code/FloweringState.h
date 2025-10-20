#ifndef FLOWERINGSTATE_H
#define FLOWERINGSTATE_H
/**
 * @file FloweringState.h
 * @brief This file contains the definition of the FloweringState class.
 */

/**
* @class FloweringState
* @brief Represents the plant being in the flowering state of its lifetime.
*/
class FloweringState : Class_Diagram,_State_and_Prototype::PlantState {

public:

	/**
	* @brief Handles the care actions specific to the flowering state.
	*/
	void handleCare();

	/**
	* @brief Transitions the plant to the next state in its lifecycle.
	*/
	void transitionToNext();
};

#endif
