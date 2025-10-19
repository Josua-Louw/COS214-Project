#ifndef SEEDS_H
#define SEEDS_H

class Seeds : Plant {


public:
	double getPrice();

	Plant* clone();

	string getType();
};

#endif
