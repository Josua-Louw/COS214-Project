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
    /**
     * @brief Gets the price of the plant.
     * @return The price of the plant as a double.
     */
    virtual double getPrice() const = 0;
    /**
     * @brief Add decoration to the given plant.
     * @param orderPlant Pointer to the plant to be decorated.
     * @return void.
     */
    virtual void decorate(OrderPlant* orderPlant) = 0;
    /**
     * @brief Gets the name of the plant.
     * @return The name of the plant as a string.
     */
    std::string getName() const;
    /*
     * @brief Gets the type of the plant.
     * @return The type of the plant as a string.
    */
    virtual std::string getType() const = 0;
    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     */
    virtual ~OrderPlant() = default;
};

#endif // ORDER_PLANT_H