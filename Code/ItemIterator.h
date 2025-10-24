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
    ItemIterator(const std::vector<Item*>& itemList);

    void first();

    void next();

    bool isDone() const;
    
    Item* currentItem() const;
};

#endif // ITEMITERATOR_H
