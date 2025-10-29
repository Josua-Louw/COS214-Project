#ifndef GREENHOUSEPLANT_H
#define GREENHOUSEPLANT_H

#include "CareStrategy.h"
#include "PlantState.h"
#include "PlantImplementor.h"
#include "NurseryMediator.h"
#include "WaterPlant.h"
#include "FertilizePlant.h"
#include "Command.h"
#include <string>
#include <atomic>
#include <vector>
#include <thread>
#include <chrono>
#include <memory>

// Forward declaration only - include SeedState.h in the .cpp file
class SeedState;
using CommandPtr = std::shared_ptr<Command>;



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
    NurseryMediator* mediator_ = nullptr;
    /**
     * @brief Pointer to the care strategy associated with this plant.
     * @details Stores a pointer to a CareStrategy object that defines the specific care actions (e.g., watering, fertilizing) required for this plant.
     */
    CareStrategy* strategy = nullptr;

    /**
     * @brief Pointer to the state the plant is currently in its lifecycle.
     * @details Stores a pointer to a PlantState object that represents the current lifecycle state of the plant (e.g., seed, seedling, mature).
     * @see PlantState
     */
    PlantState* state = nullptr;

    /**
     * @brief Name of the plant.
     * @details Stores the name of the plant as a string, used for identification.
     */
    std::string name;

    /**
     * @brief Price of the plant.
     * @details Stores the monetary value of the plant as a double.
     */
    double price = 0.0;

    std::atomic<bool> careBusy{false};
    std::atomic<bool> careSuccessful{false};
    std::atomic<bool> isAlive{true};
public:
    explicit GreenHousePlant(const std::string& name = "", double price = 0.0, NurseryMediator* mediator = nullptr, CareStrategy* care = nullptr);

    ~GreenHousePlant() override;
    /**
     * @brief Waters the plant.
     * @details Defines the interface for watering the plant, with implementation details provided by derived classes based on the plant’s type and state.
     * @return void
     */
    CommandPtr water(int time);

    /**
     * @brief Feeds the plant.
     * @details Defines the interface for feeding the plant (e.g., applying fertilizer), with implementation details provided by derived classes based on the plant’s type and state.
     * @return void
     */
    CommandPtr feed(int time);

    /**
     * @brief Gets the price of the plant.
     * @details Returns the monetary value of the plant, determined by its type and characteristics, as implemented by derived classes.
     * @return The price of the plant as a double.
     */
    double getPrice() const override;

    /**
     * @brief Creates a clone of the plant.
     * @details Produces a new instance of the plant with the same properties, as implemented by derived classes, supporting the prototype design pattern.
     * @return A pointer to the newly created clone of the plant.
     */
    PlantImplementor* clone() override;

    /**
     * @brief Gets the name of the plant.
     * @details Returns the name of the plant stored in the private member variable.
     * @return The name of the plant as a string.
     */
    std::string getName() const override;

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

    void setStrategy(CareStrategy* s) { strategy = s; }
    std::vector<Command*> applyCurrentCare();           // optional helper used by water()/feed()

    void watering(int time);
    void fertilizing(int time);

    void setMediator(NurseryMediator* m) { mediator_ = m; }

    bool getSuccess() const;
    bool getBusy() const;
    bool getIsAlive() const;
    void setSuccess(bool success);
    void setBusy(bool busy);
    void markCareStarted();              //sets busy=true, success=false
    void markCareFinished(bool success); //sets success, busy=false

    void setState(PlantState* newState);

    void killPlant();

};

#endif // GREENHOUSEPLANT_H