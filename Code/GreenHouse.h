#ifndef GREENHOUSE_H
#define GREENHOUSE_H

/**
 * @file GreenHouse.h
 * @brief Declaration of the abstract GreenHouse class.
 *
 * @class GreenHouse
 * @brief GreenHouse is the common interface for Section (composite) and Plant (leaf).
 * It defines operations used by the Composite pattern.
 * 
 * @note This class is abstract with pure virtual functions expand, sell, getSubsection, CreateIterator, and findItem.
 */

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
