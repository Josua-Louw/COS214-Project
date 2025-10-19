#ifndef DYINGSTATE_H
#define DYINGSTATE_H

class DyingState : Class_Diagram,_State_and_Prototype::PlantState {


public:
	void handleCare();

	void transitionToNext();
};

#endif
