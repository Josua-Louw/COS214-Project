#ifndef POT_H
#define POT_H

class Pot : PlantDecorator {


public:
	double getPrice();

	Plant* clone();

	string getType();
};

#endif
