#ifndef ADDSEED_H
#define ADDSEED_H

class AddSeed : OrderBuilder {


protected:
	Order* buildPart(Order* order, string itemName);

	boolean checkType(Plant* plant);
};

#endif
