#ifndef GREENHOUSEPLANT_H
#define GREENHOUSEPLANT_H

#include "CareStrategy.h"
#include "PlantState.h"
#include "PlantImplementor.h"
#include <string>

/**
 * @file Plant.h
 * @brief Defines the Plant class, the class for representing plants in the GreenHouse.
 * @details This file contains the declaration of the Plant class, which serves as the base class for all plant types in the system. It defines the interface for managing plant care, state transitions, and properties, and is part of a greenhouse system.
 */

/**
 * @class GreenHousePlant
 * @brief Class representing a plant in the greenhouse system.
 * @details The GreenHousePlant class provides a common interface for all plant types, managing their lifecycle states, care strategies, and properties such as name and price. It inherits from PlantImplementor, integrating with the greenhouse framework. The class is abstract, with pure virtual methods for watering, feeding, pricing, cloning, and type identification, which must be implemented by derived classes.
 * @see GreenHouse, CareStrategy, PlantState, SeedState, SeedlingState, JuvenileState, MatureState, FloweringState, SenescenceState, DyingState, DeadState
 */
class GreenHousePlant : public PlantImplementor {
private:
    /**
     * @brief Pointer to the care strategy associated with this plant.
     * @details Stores a pointer to a CareStrategy object that defines the specific care actions (e.g., watering, fertilizing) required for this plant.
     */
    CareStrategy* strategy;

    /**
     * @brief Pointer to the state the plant is currently in its lifecycle.
     * @details Stores a pointer to a PlantState object that represents the current lifecycle state of the plant (e.g., seed, seedling, mature).
     * @see PlantState
     */
    PlantState* state;

    /**
     * @brief Name of the plant.
     * @details Stores the name of the plant as a string, used for identification.
     */
    std::string name;

    /**
     * @brief Price of the plant.
     * @details Stores the monetary value of the plant as a double.
     */
    double price;

public:
    /**
     * @brief Waters the plant.
     * @details Defines the interface for watering the plant, with implementation details provided by derived classes based on the plant’s type and state.
     * @return void
     */
    void water();

    /**
     * @brief Feeds the plant.
     * @details Defines the interface for feeding the plant (e.g., applying fertilizer), with implementation details provided by derived classes based on the plant’s type and state.
     * @return void
     */
    void feed();

    /**
     * @brief Gets the price of the plant.
     * @details Returns the monetary value of the plant, determined by its type and characteristics, as implemented by derived classes.
     * @return The price of the plant as a double.
     */
    double getPrice() const;

    /**
     * @brief Creates a clone of the plant.
     * @details Produces a new instance of the plant with the same properties, as implemented by derived classes, supporting the prototype design pattern.
     * @return A pointer to the newly created clone of the plant.
     */
    PlantImplementor* clone();

    /**
     * @brief Gets the name of the plant.
     * @details Returns the name of the plant stored in the private member variable.
     * @return The name of the plant as a string.
     */
    std::string getName() const;

    /**
     * @brief Gets the type of the plant.
     * @details Returns a string identifying the specific type of the plant (e.g., species or category), as implemented by derived classes.
     * @return The type of the plant as a string.
     */
    PLANT_TYPE getType() const override;

    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     * @details Provides a virtual destructor to allow safe deletion of derived class objects through a Plant pointer.
     */
    virtual ~GreenHousePlant();
};

#endif // PLANT_H