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
	/**
	 * @brief Constructor for Section.
	 * @param sectionName Name of the section.
	 * @param cap Maximum capacity of items in the section before creating a new subsection.
	 */
	Section(const std::string& sectionName, size_t cap = 10);
	/**
	 * @brief Destructor for Section.
	 */
	virtual ~Section();
	/**
	 * @brief Expands the greenhouse by adding a subsection.
	 * @param greenHouse Pointer to the GreenHouse subsection to be added.
	 */
	void expand(GreenHouse* greenHouse);
	/**
	 * @brief Gets a subsection of the greenhouse by name.
	 * @param sectionName Name of the subsection to retrieve.
	 * @return Pointer to the GreenHouse subsection.
	 */
	GreenHouse* getSubsection(const std::string& sectionName);
	/**
	 * @brief Sells an item from the greenhouse.
	 * @param item Pointer to the Item to be sold.
	 * @return The sale price as a double.
	 */
	double sell(Item* item);
	/**
	 * @brief Creates an iterator for traversing the greenhouse structure.
	 * @return Pointer to an Iterator for GreenHouse items.
	 */
	Iterator<Item*>* createIterator();
	/**
	 * @brief Finds an item in the greenhouse by name.
	 * @param itemName Name of the item to find.
	 * @return Pointer to the found Item, or nullptr if not found.
	 */
	Item* findItem(const std::string& itemName);
	/**
	 * @brief Adds an item to the section.
	 * @param item Pointer to the Item to be added.
	 */
	void addItem(Item* item);
	/**
	 * @brief Gets the name of the section.
	 * @return The name of the section as a string.
	 */
	std::string getName() const;
	/**
	 * @brief Gets the count of items in the section.
	 * @return The number of items in the section as a size_t.
	 */
	size_t getItemCount() const;
	/**
	 * @brief Prints a summary of the section and its items.
	 */
	void printSummary() const;
	/**
	 * @brief Gets the total item count in the greenhouse.
	 * @return The total number of items as a size_t.
	 */
	size_t getTotalItemCount() const;
	/**
	 * @brief Helper function to print summary with indentation.
	 * @param indentLevel Level of indentation for formatting.
	 */
	void printSummaryHelper(int indentLevel) const;
};

#endif
