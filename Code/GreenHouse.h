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
 * @note This class is abstract with pure virtual functions expand, sell, getSubsection, createIterator, findItem, getName, printSummary.
 */
class GreenHouse {
private:
	NurseryMediator* nurseryHub;

public:
	virtual ~GreenHouse() {}

	virtual void expand(GreenHouse* greenHouse) = 0;

	virtual double sell(Item* item) = 0;

	virtual GreenHouse* getSubsection(const std::string& sectionName) = 0;

	virtual Iterator<Item*>* createIterator() = 0;

	virtual Item* findItem(const std::string& itemName) = 0;

	virtual std::string getName() const = 0;

	virtual void printSummary() const = 0;

	virtual size_t getTotalItemCount() const = 0;

	virtual void printSummaryHelper(int indentLevel) const = 0;
};

#endif
