#ifndef POT_H
#define POT_H

#include "PlantDecorator.h"

class Pot : public PlantDecorator {
public:
	double getPrice();

	Plant* clone();

	std::string getType();
};

#endif
