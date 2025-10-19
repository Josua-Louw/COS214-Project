#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

class PlantDecorator : Plant {

public:
	Plant* component;

	double getPrice();

	Plant* clone();
};

#endif
