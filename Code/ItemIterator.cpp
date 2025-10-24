#include "ItemIterator.h"
#include <iostream>

/**
 * @file ItemIterator.cpp
 * @brief Implementation of ItemIterator methods.
 * It is responsible for traversing collections of Item objects within a GreenHouse (Composite structure).
 */

/**
 * @brief Construct a new ItemIterator object.
 * 
 * @param itemList Vector of Item pointers to iterate over.
 */
ItemIterator::ItemIterator(const std::vector<Item*>& itemList)
    : items(itemList), currentIndex(0) {}

static size_t advance_to_next_valid(const std::vector<Item*>& arr, size_t idx) {            //HELPER
    size_t n = arr.size();
    while (idx < n && arr[idx] == nullptr) ++idx;
    return idx;
}
    
/**
 * @brief This method resets the iterator to the first element of the container (the first Item in a (sub)section).
 * 
 * @note Typically called before a loop begins to ensure iteration starts from the beginning.
*/
void ItemIterator::first() {
    currentIndex = advance_to_next_valid(items, 0);
}

/**
 * @brief Advances the iterator to the next Item object in the collection/list.
 * After calling this method, the iterator points to the next Item, if it exists. 
 * If the end of the collection is reached, subsequent calls to next() should have 
 * no effect, and isDone() should return true.
 */
void ItemIterator::next() {
    if (currentIndex < items.size()) {
        ++currentIndex;
        currentIndex = advance_to_next_valid(items, currentIndex);
    }
}

/**
 * @brief Checks if the iterator has reached the end of the Item collection.
 * 
 * @return true if all Items have been visited, false otherwise.
 *
 * @note This method allows client code to determine when iteration is complete.
 */
bool ItemIterator::isDone() const {
    size_t idx = currentIndex;
    idx = advance_to_next_valid(items, idx);
    return idx >= items.size();
}

/**
 * @brief Returns the current Item object that the iterator points to.
 * 
 * @return Pointer to the current Item object.
 *
 * @note If the iterator is at a valid position, this method retrieves the current 
 * Item for processing. If the iterator is at the end (isDone() == true), 
 * this method may return nullptr.
 */
Item* ItemIterator::currentItem() const {
    size_t idx = currentIndex;
    idx = advance_to_next_valid(items, idx);
    if (idx < items.size()){
        return items[idx];
    }
    return nullptr;
}
