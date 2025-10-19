#ifndef ADDDECORATION_H
#define ADDDECORATION_H

class AddDecoration : OrderBuilder {


protected:
	Order* buildPart(Order* order, string itemName);

	boolean checkType(Plant* plant);
};

#endif
