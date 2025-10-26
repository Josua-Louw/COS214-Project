#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <string>
#include <vector>
#include "Iterator.h"

class NurseryMediator;
class Plant;

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

	virtual GreenHouse* getSubsection(std::string sectionName) = 0;

	virtual Iterator* CreateIterator() = 0;

	virtual Plant* findItem(std::string itemName) = 0;
};

#endif
