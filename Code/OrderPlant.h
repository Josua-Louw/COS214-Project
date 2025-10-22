#ifndef ORDER_PLANT_H
#define ORDER_PLANT_H

#include "PlantImplementor.h"
#include <string>

/**
 * @file OrderPlant.h
 * @brief This file contains the definition of the OrderPlant class.
 */

 /**
  * @class OrderPlant
  * @brief Abstract base class representing an orderable plant.
  * @details The OrderPlant class serves as an abstract base class for all orderable plants in the system. It defines the interface for getting the price, decorating the plant, and retrieving the
  * type of the plant. Derived classes must implement these methods to provide specific behavior for different types of orderable plants.
  * @note This class is abstract and cannot be instantiated directly.
  * @see PlantImplementor, PlantDecorator, SeedPacket, Decoration, Pot
  * @todo Implement concrete classes for different types of orderable plants.
  * @warning This class is not intended for direct use.
  */

class OrderPlant : public PlantImplementor {
protected:
    double cost;
    std::string name;
public:
    OrderPlant() = default;
    OrderPlant(const OrderPlant&) = default;
    virtual double getPrice() const = 0;
    virtual void decorate(OrderPlant* orderPlant) = 0;
    std::string getName() const;
    virtual std::string getType() const = 0;
    virtual ~OrderPlant() = default;
};

#endif // ORDER_PLANT_H