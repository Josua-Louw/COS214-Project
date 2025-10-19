#ifndef SENESCENCESTATE_H
#define SENESCENCESTATE_H

class SenescenceState : Class_Diagram,_State_and_Prototype::PlantState {


public:
	void handleCare();

	void transitionToNext();
};

#endif
