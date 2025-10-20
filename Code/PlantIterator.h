#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H

/**
 * @file PlantIterator.h
 * @brief Declaration of the concrete PlantIterator class.
 *
 * @class PlantIterator
 * @brief Concrete iterator that traverses Plant nodes inside GreenHouse section(s).
 * 
 * @note This class inherits from the abstract Iterator class. 
 * @implements first
 * @implements next
 * @implements isDone
 * @implements currentItem
 */

class PlantIterator : Iterator {

public:
	void first();

	void next();

	boolean isDone();

	Plant* currentItem();
};

#endif
