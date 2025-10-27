#ifndef ITEM_H
#define ITEM_H

#include "GreenHouse.h"

/**
 * @file Item.h
 * @brief This file contains the definition of the Item class.
 * @details The Item class represents a generic item in the greenhouse system. It provides an interface for getting the name of the item.
 */

 /**
  * @class Item
  * @brief Abstract base class representing a generic item in the greenhouse system.
  * @details The Item class provides a common interface for all items in the greenhouse system,
  * allowing for retrieval of the item's name. It is an abstract class with a pure virtual method for getting the name, which must be implemented by derived classes.
  * @note This class is abstract and cannot be instantiated directly.
  * @see GreenHouse
  */

class Item : public GreenHouse {
public:
    /**
     * @brief Gets the name of the item.
     * @return The name of the item as a string.
     */
    virtual std::string getName() const = 0;
    /**
     * @brief Gets the price of the item.
     * @return The price of the item as a double.
     */
    virtual double getPrice() const = 0;

    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     */
    virtual ~Item() = default;

    void expand(GreenHouse* gh) override;
    double sell(Item* item) override;
    GreenHouse* getSubsection(const std::string& sectionName) override;
    Iterator<Item*>* createIterator() override;
    Item* findItem(const std::string& itemName) override;
    void printSummary() const override;
    size_t getTotalItemCount() const;
    void printSummaryHelper(int indentLevel) const;
};

#endif // ITEM_H