#ifndef DEADSTATE_H
#define DEADSTATE_H

class DeadState : Class_Diagram,_State_and_Prototype::PlantState {


public:
	void handleCare();

	void transitionToNext();
};

#endif
