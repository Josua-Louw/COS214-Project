#ifndef DECORATION_H
#define DECORATION_H

class Decoration : PlantDecorator {


public:
	double getPrice();

	void addRibbon();

	void addCard();

	Plant* clone();

	string getType();
};

#endif
