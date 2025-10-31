#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include <atomic>
#include <iostream>

/**
 * @file PlantState.h
 * @brief Defines the PlantState class, the abstract base class for plant lifecycle states.
 * @details This file contains the declaration of the PlantState class, which serves as the base class for all states in the plant lifecycle state machine. It defines the interface for handling care actions and state transitions.
 */

class GreenHousePlant;

/**
 * @class PlantState
 * @brief Abstract base class representing a state in a plant's lifecycle.
 * @details The PlantState class provides a common interface for all plant lifecycle states, such as seed, seedling, juvenile, mature, flowering, senescence, dying and dead states. It is an abstract class with pure virtual methods for handling care actions and transitioning to the next state. Derived classes implement specific behavior for each lifecycle stage.
 * @note This class is abstract and cannot be instantiated directly.
 * @see SeedState, SeedlingState, JuvenileState, MatureState, FloweringState, SenescenceState, DyingState, DeadState
 */
class PlantState {
protected:
    std::atomic<bool> plantAlive{true};
    GreenHousePlant* plant_ = nullptr;
public:

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Defines the interface for transitioning the plant to its next lifecycle state, which may depend on care actions or other conditions. Derived classes implement this method to specify the next state (e.g., from seedling to juvenile or dying).
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return void
     * @see SeedState, SeedlingState, JuvenileState, MatureState, FloweringState, SenescenceState, DyingState, DeadState
     */
    virtual void transitionToNext() = 0;

    /**
     * @brief Virtual destructor to ensure proper cleanup in derived classes.
     * @details Provides a virtual destructor to allow safe deletion of derived class objects through a PlantState pointer.
     */
    virtual ~PlantState() {std::cout << "deleting PlantState" << std::endl;};

    explicit PlantState(GreenHousePlant* plant) : plant_(plant) {};

    void setPlantAlive(bool plantExist);

    bool isAlive() const;
};

#endif // PLANTSTATE_H