#ifndef SECTION_H
#define SECTION_H

#include "GreenHouse.h"

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
 * @implements expand
 * @implements getSubsection
 * @implements sell
 * @implements CreateIterator
 * @implements findItem
 */


class Section : GreenHouse {

public:
	std::vector<GreenHouse*> Subsection;

	void expand(GreenHouse* greenHouse);

	GreenHouse* getSubsection(std::string sectionName);

	double sell(GreenHouse* Item);

	Iterator* CreateIterator();

	Plant* findItem(std::string itemName);
};

#endif
