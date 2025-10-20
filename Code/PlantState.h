#ifndef PLANTSTATE_H
#define PLANTSTATE_H

/**
 * @file PlantState.h
 * @brief Defines the PlantState class, the abstract base class for plant lifecycle states.
 * @details This file contains the declaration of the PlantState class, which serves as the base class for all states in the plant lifecycle state machine. It defines the interface for handling care actions and state transitions.
 */

/**
 * @class PlantState
 * @brief Abstract base class representing a state in a plant's lifecycle.
 * @details The PlantState class provides a common interface for all plant lifecycle states, such as seed, seedling, juvenile, mature, flowering, senescence, dying and dead states. It is an abstract class with pure virtual methods for handling care actions and transitioning to the next state. Derived classes implement specific behavior for each lifecycle stage.
 * @note This class is abstract and cannot be instantiated directly.
 * @see SeedState, SeedlingState, JuvenileState, MatureState, FloweringState, SenescenceState, DyingState, DeadState
 */
class PlantState {
public:
    /**
     * @brief Handles care actions specific to the current state.
     * @details Defines the interface for performing care actions (e.g., watering, fertilizing) appropriate to the plant’s current lifecycle state. Derived classes implement this method to provide state-specific care logic.
     * @note This is a pure virtual method, requiring implementation in derived classes.
     * @return void
     */
    virtual void handleCare() = 0;

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
    virtual ~PlantState() = default;
};

#endif // PLANTSTATE_H