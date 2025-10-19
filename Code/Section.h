#ifndef SECTION_H
#define SECTION_H

class Section : GreenHouse {

public:
	vector<GreenHouse> Subsection;

	void expand(GreenHouse* greenHouse);

	GreenHouse* getSubsection(string sectionName);

	double sell(GreenHouse* Item);

	Iterator* CreateIterator();

	Plant* findItem(string itemName);
};

#endif
