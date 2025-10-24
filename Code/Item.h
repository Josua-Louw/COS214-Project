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
    virtual std::string getName() const = 0;

    virtual double getPrice() const = 0;

    virtual ~Item() = default;
};

#endif // ITEM_H