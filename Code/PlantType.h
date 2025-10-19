#ifndef PLANTTYPE_H
#define PLANTTYPE_H

class PlantType : PlantDecorator {

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

	string getType();
};

#endif
