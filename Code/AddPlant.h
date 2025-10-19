#ifndef ADDPLANT_H
#define ADDPLANT_H

class AddPlant : OrderBuilder {


protected:
	Order* buildPart(Order* order, string itemName);

	boolean checkType(Plant* plant);
};

#endif
