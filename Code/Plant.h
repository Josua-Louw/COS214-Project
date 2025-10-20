#ifndef PLANT_H
#define PLANT_H

#include "CareStrategy.h"
#include "PlantState.h"
#include "GreenHouse.h"
#include <string>

/**
 * @file Plant.h
 * @brief Defines the Plant class, the abstract base class for representing plants.
 * @details This file contains the declaration of the Plant class, which serves as the base class for all plant types in the system. It defines the interface for managing plant care, state transitions, and properties, and is part of a greenhouse system.
 */

/**
 * @class Plant
 * @brief Abstract base class representing a plant in the greenhouse system.
 * @details The Plant class provides a common interface for all plant types, managing their lifecycle states, care strategies, and properties such as name and price. It inherits from GreenHouse, integrating with the greenhouse framework. The class is abstract, with pure virtual methods for watering, feeding, pricing, cloning, and type identification, which must be implemented by derived classes.
 * @note This class is abstract and cannot be instantiated directly.
 * @see GreenHouse, CareStrategy, PlantState, SeedState, SeedlingState, JuvenileState, MatureState, FloweringState, SenescenceState, DyingState, DeadState
 */
class Plant : public GreenHouse {
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

public:
    /**
     * @brief Waters the plant.
     * @details Defines the interface for watering the plant, with implementation details provided by derived classes based on the plant’s type and state.
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return void
     */
    virtual void water() = 0;

    /**
     * @brief Feeds the plant.
     * @details Defines the interface for feeding the plant (e.g., applying fertilizer), with implementation details provided by derived classes based on the plant’s type and state.
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return void
     */
    virtual void feed() = 0;

    /**
     * @brief Gets the price of the plant.
     * @details Returns the monetary value of the plant, determined by its type and characteristics, as implemented by derived classes.
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return The price of the plant as a double.
     */
    virtual double getPrice() = 0;

    /**
     * @brief Creates a clone of the plant.
     * @details Produces a new instance of the plant with the same properties, as implemented by derived classes, supporting the prototype design pattern.
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return A pointer to the newly created clone of the plant.
     */
    virtual Plant* clone() = 0;

    /**
     * @brief Gets the name of the plant.
     * @details Returns the name of the plant stored in the private member variable.
     * @return The name of the plant as a string.
     */
    std::string getName();

    /**
     * @brief Gets the type of the plant.
     * @details Returns a string identifying the specific type of the plant (e.g., species or category), as implemented by derived classes.
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return The type of the plant as a string.
     */
    virtual std::string getType() = 0;

    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     * @details Provides a virtual destructor to allow safe deletion of derived class objects through a Plant pointer.
     */
    virtual ~Plant() = default;
};

#endif // PLANT_H