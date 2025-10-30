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
	/**
	 * @brief Virtual destructor for proper cleanup of derived classes.
	 */
	virtual ~Iterator() = default;

	/**
	 * @brief Resets the iterator to the first element in the collection.
	 */
	virtual void first() = 0;
	/**
	 * @brief Advances the iterator to the next element in the collection.
	 */
	virtual void next() = 0;
	/**
	 * @brief Checks if the iterator has reached the end of the collection.
	 * @return true if all elements have been iterated over, false otherwise.
	 */
	virtual bool isDone() const = 0;
	/**
	 * @brief Gets the current element in the iteration.
	 * @return The current element of type T.
	 */
	virtual T currentItem() const = 0;
};

#endif
