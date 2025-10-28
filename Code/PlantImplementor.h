#ifndef PLANT_IMPLEMENTOR_H
#define PLANT_IMPLEMENTOR_H

#include <string>
/**
 * @file PlantImplementor.h
 * @brief Defines the PlantImplementor class, an abstract base class for plant implementors.
 * @details This file contains the declaration of the PlantImplementor class, which serves as an abstract base class for different plant implementors in the system. It defines the interface for cloning plant implementors.
 */

enum class PLANT_TYPE {
    SEED_PACKET,
    DECORATION,
    POT,
    ORDER_PLANT,
    GREENHOUSE_PLANT
};

 /**
  * @class PlantImplementor
  * @brief Abstract base class for plant implementors.
  * @details The PlantImplementor class provides a common interface for all plant implementors, allowing for cloning of plant implementor objects. It is an abstract class with a pure virtual method for cloning, which must be implemented by derived classes.
  * @note This class is abstract and cannot be instantiated directly.
  */
class PlantImplementor {
public:
    /**
     * @brief Default constructor.
     */
    PlantImplementor() = default;
    /**
     * @brief Copy constructor.
     * @param other The PlantImplementor object to copy from.
     */
    PlantImplementor(const PlantImplementor&) = default;
    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     */
    virtual ~PlantImplementor() = default;
    /**
     * @brief Clones the plant implementor.
     * @return A pointer to a new PlantImplementor object that is a copy of the current object.
     */
    virtual PlantImplementor* clone() = 0;
    /**
     * @brief Gets the price of the plant implementor.
     * @return The price of the plant implementor as a double.
     */
    virtual double getPrice() const = 0;
    /**
     * @brief Gets the name of the plant implementor.
     * @return The name of the plant implementor as a string.
     */
    virtual std::string getName() const = 0;
    /**
     * @brief Gets the type of the plant implementor.
     * @return The type of the plant implementor as a PLANT_TYPE enum.
     */
    virtual PLANT_TYPE getType() const = 0;
};

#endif // PLANT_IMPLEMENTOR_H