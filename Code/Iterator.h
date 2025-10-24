#ifndef ITERATOR_H
#define ITERATOR_H

class Plant; // Forward declaration
class Item; // Forward declaration

/**
 * @file Iterator.h
 * @brief Declaration of the abstract templated Iterator class.
 *
 * @class Iterator
 * @brief Templated abstract interface defining the traversal operations for iterating
 * over collections of type T objects in the GreenHouse system.
 *
 * @tparam T The type of element to iterate over (e.g., Plant*, Item*, etc.)
 * 
 * @note This class is abstract with pure virtual functions first, next, isDone, currentItem.
 * Consider templating this class (Iterator<T>) later to allow for the creators of iterators for staff, customers, etc.
 */

template <typename T>
class Iterator {
public:
	virtual ~Iterator() = default;

	virtual void first() = 0;

	virtual void next() = 0;

	virtual bool isDone() const = 0;

	virtual T currentItem() const = 0;
};

#endif
