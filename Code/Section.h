#ifndef SECTION_H
#define SECTION_H

#include "GreenHouse.h"
#include "Item.h"
#include "Iterator.h"
#include "ItemIterator.h"
#include "Plant.h"
#include "PotAdapter.h"
#include "DecorationAdapter.h"
#include "SeedPacketAdapter.h"
#include <string>
#include <vector>
#include <iostream>

/**
 * @file Section.h
 * @brief Declaration of the concrete Section class.
 *
 * @class Section
 * @brief Section is the concrete composite class.
 * It implements operations used by the Composite pattern, such as adding additional subsections 
 * to the greenhouse by aggregating child GreenHouse pointers.
 * 
 * @note This class inherits from the GreenHouse abstract class. 
 * @implements Section
 * @implements ~Section
 * @implements expand
 * @implements getSubsection
 * @implements sell
 * @implements createIterator
 * @implements findItem
 * @implements addItem
 * @implements getName
 * @implements getItemCount
 * @implements printSummary
 */


class Section : public GreenHouse {
private:
    std::string name;                   
    std::vector<GreenHouse*> section; 
    std::vector<Item*> items;             // All items (including plants, pots, etc.)
    size_t capacity;                      //This refers to the max number of items before creating new subsection

public:
	Section(const std::string& sectionName, size_t cap = 10);

	virtual ~Section();

	void expand(GreenHouse* greenHouse);

	GreenHouse* getSubsection(const std::string& sectionName);

	double sell(Item* item);

	Iterator<Item*>* createIterator();

	Item* findItem(const std::string& itemName);

	void addItem(Item* item);

	std::string getName() const;

	size_t getItemCount() const;

	void printSummary() const;

	size_t getTotalItemCount() const;

	void printSummaryHelper(int indentLevel) const;
};

#endif
