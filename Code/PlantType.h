#ifndef PLANTTYPE_H
#define PLANTTYPE_H

#include "PlantDecorator.h"

class PlantType : public PlantDecorator {

private:
	int seedlingTime;
	int juvenileTime;
	int matureTime;
	int timeForNextCare;

public:
	void water();

	void feed();

	double getPrice();

	Plant* clone();

	std::string getType();
};

#endif
