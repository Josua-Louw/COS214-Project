#ifndef ORDERBUILDER_H
#define ORDERBUILDER_H

class OrderBuilder {

protected:
	GreenHouse* greenHouse;

public:
	virtual Order* buildPart(Order* order, string itemName) = 0;

protected:
	virtual boolean checkType(Plant* plant) = 0;
};

#endif
