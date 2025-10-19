#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H

class PlantIterator : Iterator {


public:
	void first();

	void next();

	boolean isDone();

	Plant* currentItem();
};

#endif
