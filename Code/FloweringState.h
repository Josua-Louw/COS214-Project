#ifndef FLOWERINGSTATE_H
#define FLOWERINGSTATE_H

class FloweringState : Class_Diagram,_State_and_Prototype::PlantState {


public:
	void handleCare();

	void transitionToNext();
};

#endif
