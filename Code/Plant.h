#ifndef PLANT_H
#define PLANT_H

#include "Item.h"
#include "PlantImplementor.h"

/**
 * @file Plant.h
 * @brief Defines the Plant class, the class for representing plants overall.
 * @details This file contains the declaration of the Plant class, which serves as the class which can be implemented by different plant class which are namely GreenHousePlant and OrderPlant.
 */

 /**
  * @class Plant
  * @brief Class representing a plant in the system.
  * @details The Plant class provides a common interface for all plant types, managing their properties such as price and implementor type. It inherits from GreenHouse, integrating with the greenhouse framework.
  * @see GreenHouse, PlantImplementor, GreenHousePlant, OrderPlant
  */
class Plant : public Item
{
private:
    /**
     * @brief Pointer to the implementor associated with this plant.
     * @details Stores a pointer to a PlantImplementor object that defines the specific implementation details for this plant.
     */
    PlantImplementor* implementor;
public:
    Plant();
    /**
     * @brief Converts the plant to an order type.
     * @details Defines the interface for converting the plant to an order type, with implementation details provided by derived classes based on the plant’s type.
     * @return void
     */
    void convertToOrderType();
    /**
     * @brief Gets the price of the plant.
     * @details Defines the interface for retrieving the price of the plant, with implementation details provided
     * by derived classes based on the plant’s type.
     * @return double The price of the plant.
     */
    double getPrice();
    /**
     * @brief Gets the implementor type of the plant.
     * @details Defines the interface for retrieving the implementor type of the plant, with implementation details provided
     * by derived classes based on the plant’s type.
     * @return std::string The implementor type of the plant.
     */
    std::string getImplementorType();
    /**
     * @brief Gets the name of the plant.
     * @details Overrides the getName method from the Item class to provide the name of the plant.
     * @return std::string The name of the plant.
     */
    std::string getName() const override;
    ~Plant();
};

#endif // PLANT_H