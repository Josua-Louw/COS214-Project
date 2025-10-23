#ifndef PLANT_IMPLEMENTOR_H
#define PLANT_IMPLEMENTOR_H

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
    PlantImplementor() = default;
    PlantImplementor(const PlantImplementor&) = default;
    virtual ~PlantImplementor() = default;
    virtual PlantImplementor* clone() = 0;
    virtual PLANT_TYPE getType() const = 0;
};

#endif // PLANT_IMPLEMENTOR_H