#include "FertilizerBoostStrategy.h"
#include "GreenHousePlant.h"
/**
 * @file FertilizerBoostStrategy.cpp
 * @brief Implementation of the FertilizerBoostStrategy class.
 *
 * Contains the definitions for applying fertilizer-based care to a plant
 * and retrieving the strategy’s identifying name.
 */

/**
 * @brief Applies fertilizer-based care to the plant.
 *
 * @note This method is part of the Strategy pattern and defines
 * how this specific care approach benefits the plant.
 */
std::vector<Command*> FertilizerBoostStrategy::applyCare(GreenHousePlant& plant) {
    plant.setSuccess(false);
    plant.setBusy(false);
    return { plant.water(2), plant.feed(4) };
}

/**
 * @brief Returns the identifying name of this strategy.
 *
 * @note Used for debugging or UI purposes to indicate which
 * care strategy is currently active.
 */
std::string FertilizerBoostStrategy::getStrategyName() const {
	return "FertilizerBoost";
}
