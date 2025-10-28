#ifndef ITEMITERATOR_H
#define ITEMITERATOR_H

#include "Iterator.h"
#include "Item.h"
#include <vector>

/**
 * @file ItemIterator.h
 * @brief Declaration of the concrete ItemIterator class.
 *
 * @class ItemIterator
 * @brief Concrete iterator that traverses Item nodes inside GreenHouse section(s).
 *
 * @details Iterates through a collection of Item pointers (e.g., pots, decorations, or seed packets).
 * @note This class inherits from the abstract Iterator class. 
 * @implements first
 * @implements next
 * @implements isDone
 * @implements currentItem
 */

class ItemIterator : public Iterator<Item*> {
private:
    std::vector<Item*> items; 
    size_t currentIndex;      

public:
    /**
     * @brief Constructs an ItemIterator with a list of Item pointers.
     * @param itemList Vector of Item pointers to iterate over.
     */
    ItemIterator(const std::vector<Item*>& itemList);
    /**
     * @brief Resets the iterator to the first item.
     */
    void first();
    /**
     * @brief Advances the iterator to the next item.
     */
    void next();
    /**
     * @brief Checks if the iterator has reached the end of the collection.
     * @return true if all items have been iterated over, false otherwise.
     */
    bool isDone() const;
    /**
     * @brief Gets the current item in the iteration.
     * @return Pointer to the current Item.
     */
    Item* currentItem() const;
};

#endif // ITEMITERATOR_H
