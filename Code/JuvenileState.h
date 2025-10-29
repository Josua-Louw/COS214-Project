#ifndef JUVENILESTATE_H
#define JUVENILESTATE_H

#include <thread>
#include <chrono>
#include <memory>

#include "PlantState.h"
#include "MatureState.h"
#include "DyingState.h"

using CommandPtr = std::shared_ptr<Command>;

/**
 * @file JuvenileState.h
 * @brief Defines the JuvenileState class for representing a plant's juvenile phase.
 * @details This file contains the declaration of the JuvenileState class, which is part of the plant lifecycle state machine. It represents the stage where the plant is actively growing but not yet mature, requiring consistent care to develop further.
 */

/**
 * @class JuvenileState
 * @brief Represents the juvenile state in a plant's lifecycle.
 * @details The JuvenileState class models the phase where the plant is actively growing, developing its structure and strength before reaching maturity. It inherits from PlantState, part of the plant lifecycle state machine. Care actions, such as watering and fertilizing, are essential to support growth and enable progression to the mature state.
 * @note This stage is critical for establishing the plant’s foundation for maturity.
 * @see PlantState, MatureState, DyingState
 */
class JuvenileState : public PlantState {
public:

    /**
     * @brief Transitions the plant to the next state in its lifecycle.
     * @details Moves the plant from the juvenile state to the mature state if appropriate care has been provided. If care is insufficient, the plant transitions to the dying state.
     * @note The next state is typically the MatureState or, in case of inadequate care, the DyingState.
     * @return void
     * @see MatureState, DyingState
     */
    void transitionToNext() override;

    explicit JuvenileState(GreenHousePlant* plant);
};

#endif // JUVENILESTATE_H