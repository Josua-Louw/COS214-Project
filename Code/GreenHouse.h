#ifndef GREENHOUSE_H
#define GREENHOUSE_H

class GreenHouse {

private:
	NurseryMediator* nurseryHub;

public:
	virtual void expand(GreenHouse* greenHouse) = 0;

	virtual double sell(GreenHouse* Item) = 0;

	virtual GreenHouse* getSubsection(string sectionName) = 0;

	virtual Iterator* CreateIterator() = 0;

	virtual Plant* findItem(string itemName) = 0;
};

#endif
