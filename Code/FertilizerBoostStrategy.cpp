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
    Command* returnWater = plant.water(2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    Command* returnFeed = plant.feed(4);
    return { returnWater, returnFeed};
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
