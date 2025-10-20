#include "../Visual Paradigm files/PlantIterator.h"

/**
 * @file PlantIterator.cpp
 * @brief Implementation of the concrete PlantIterator class.
 * It is responsible for traversing collections of Plant objects within a GreenHouse (Composite structure).
 * 
 * @todo Implement the methods first, next, isDone, and currentItem methods.
*/

/**
 * @brief This method resets the iterator to the first element of the container (the first Plant in a (sub)section).
 * 
 * @note Typically called before a loop begins to ensure iteration starts from the beginning.
*/ 
void PlantIterator::first() {
	// TODO - implement PlantIterator::first
	throw "Not yet implemented";
}

/**
 * @brief Advances the iterator to the next Plant object in the collection/list.
 * After calling this method, the iterator points to the next Plant, if it exists. 
 * If the end of the collection is reached, subsequent calls to next() should have 
 * no effect, and isDone() should return true.
 */
void PlantIterator::next() {
	// TODO - implement PlantIterator::next
	throw "Not yet implemented";
}

/**
 * @brief Checks if the iterator has reached the end of the Plant collection.
 * 
 * @return true if all Plants have been visited, false otherwise.
 *
 * @note This method allows client code to determine when iteration is complete.
 */
boolean PlantIterator::isDone() {
	// TODO - implement PlantIterator::isDone
	throw "Not yet implemented";
}

/**
 * @brief Returns the current Plant object that the iterator points to.
 * 
 * @return Pointer to the current Plant object.
 *
 * @note If the iterator is at a valid position, this method retrieves the current 
 * Plant for processing. If the iterator is at the end (isDone() == true), 
 * this method may return nullptr.
 */
Plant* PlantIterator::currentItem() {
	// TODO - implement PlantIterator::currentItem
	throw "Not yet implemented";
}
