#ifndef ADDPOT_H
#define ADDPOT_H

class AddPot : OrderBuilder {


protected:
	Order* buildPart(Order* order, string itemName);

	boolean checkType(Plant* plant);
};

#endif
