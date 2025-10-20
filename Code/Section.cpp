#include "Section.h"

/**
 * @file Section.cpp
 * @brief Implementation of the Section class.
 * 
 * @todo Implement the methods expand, getSubsection, sell, CreateIterator, and findItem methods.
*/

/**
 * @brief Expands the greenhouse by adding a subsection (leaf) of the GreenHouse class.
 * 
 * @param greenHouse Pointer to the current subsection to be added (composite).
*/ 
void Section::expand(GreenHouse* greenHouse) {
	// TODO - implement Section::expand
	throw "Not yet implemented";
}

/**
 * @brief Searches the greenhouse for a specific subsection (leaf) that belongs to the GreenHouse class.
 * 
 * @param sectionName String description of the section to be searched for.
 * 
 * @return Pointer to the greenhouse section that was searched for, or nullptr if not found.
*/ 
GreenHouse* Section::getSubsection(std::string sectionName) {
	// TODO - implement Section::getSubsection
	throw "Not yet implemented";
}

/**
 * @brief Sell an item represented by the given GreenHouse node.
 * 
 * @param Item GreenHouse node (usually a Plant* or Section* that is to be sold).
 * 
 * @return Total price of the item (double).
*/ 
double Section::sell(GreenHouse* Item) {
	// TODO - implement Section::sell
	throw "Not yet implemented";
}

/**
 * @brief Create a concrete iterator for traversing contained items (usually plant items).
 * 
 * @return Pointer to the dynamically allocated Iterator* (caller responsible for delete).
*/ 
Iterator* Section::CreateIterator() {
	// TODO - implement Section::CreateIterator
	throw "Not yet implemented";
}

/**
 * @brief Find a plant by name (string) inside this node/subsection of the greenhouse.
 * 
 * @param itemName Plant name to be searched for.
 * 
 * @return Pointer to the plant item (Plant*), otherwise nullptr if not found.
*/ 
Plant* Section::findItem(std::string itemName) {
	// TODO - implement Section::findItem
	throw "Not yet implemented";
}
