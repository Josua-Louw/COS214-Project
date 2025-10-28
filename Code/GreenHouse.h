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
	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~GreenHouse() {}
	/**
	 * @brief Expands the greenhouse by adding a subsection.
	 * @param greenHouse Pointer to the GreenHouse subsection to be added.
	 */
	virtual void expand(GreenHouse* greenHouse) = 0;
	/**
	 * @brief Sells an item from the greenhouse.
	 * @param item Pointer to the Item to be sold.
	 * @return The sale price as a double.
	 */
	virtual double sell(Item* item) = 0;
	/**
	 * @brief Gets a subsection of the greenhouse by name.
	 * @param sectionName Name of the subsection to retrieve.
	 * @return Pointer to the GreenHouse subsection.
	 */
	virtual GreenHouse* getSubsection(const std::string& sectionName) = 0;
	/**
	 * @brief Creates an iterator for traversing the greenhouse structure.
	 * @return Pointer to an Iterator for GreenHouse items.
	 */
	virtual Iterator<Item*>* createIterator() = 0;
	/**
	 * @brief Finds an item in the greenhouse by name.
	 * @param itemName Name of the item to find.
	 * @return Pointer to the found Item, or nullptr if not found.
	 */
	virtual Item* findItem(const std::string& itemName) = 0;
	/**
	 * @brief Gets the name of the greenhouse section or item.
	 * @return The name as a string.
	 */
	virtual std::string getName() const = 0;
	/**
	 * @brief Prints a summary of the greenhouse section or item.
	 */
	virtual void printSummary() const = 0;
	/**
	 * @brief Gets the total item count in the greenhouse.
	 * @return The total number of items as a size_t.
	 */
	virtual size_t getTotalItemCount() const = 0;
	/**
	 * @brief Helper function to print summary with indentation.
	 * @param indentLevel Level of indentation for formatting.
	 */
	virtual void printSummaryHelper(int indentLevel) const = 0;
};

#endif
