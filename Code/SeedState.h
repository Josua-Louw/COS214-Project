#ifndef SEEDSTATE_H
#define SEEDSTATE_H

class SeedState : Class_Diagram,_State_and_Prototype::PlantState {


public:
	void handleCare();

	void transitionToNext();
};

#endif
