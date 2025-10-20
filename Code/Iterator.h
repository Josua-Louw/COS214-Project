#ifndef ITERATOR_H
#define ITERATOR_H

/**
 * @file Iterator.h
 * @brief Declaration of the abstract Iterator class.
 *
 * @class Iterator
 * @brief Non-templated abstract iterator for Plant traversal.
 *
 * @note This class is abstract with pure virtual functions first, next, isDone, currentItem.
 * Consider templating this class (Iterator<T>) later to allow for the creators of iterators for staff, customers, etc.
 */

class Iterator {


public:
	virtual void first() = 0;

	virtual void next() = 0;

	virtual boolean isDone() = 0;

	virtual Plant* currentItem() = 0;
};

#endif
