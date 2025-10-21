#ifndef DECORATION_H
#define DECORATION_H

#include "PlantDecorator.h"

class Decoration : public PlantDecorator {


public:
	double getPrice();

	void addRibbon();

	void addCard();

	Plant* clone();

	std::string getType();
};

#endif
