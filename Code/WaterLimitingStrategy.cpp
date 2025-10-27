#include "WaterLimitingStrategy.h"
#include "GreenHousePlant.h"

/**
 * @file WaterLimitingStrategy.cpp
 * @brief Implementation of the WaterLimitingStrategy class.
 *
 * Defines the behavior for limiting water supply to plants that benefit from
 * controlled hydration levels.
 */

/**
 * @brief Applies a limited watering schedule to the plant.
 *
 * @note This method implements the behavior of the water-limiting care strategy.
 */
std::vector<Command*> WaterLimitingStrategy::applyCare(GreenHousePlant& plant) {
    plant.setSuccess(false);
    plant.setBusy(false);
    return { plant.water(1), plant.feed(2) };
}

/**
 * @brief Returns the identifying name of this strategy.
 *
 * @return The name of the care strategy ("Water Limiting Strategy").
 */
std::string WaterLimitingStrategy::getStrategyName() const {
	return "WaterLimiting";
}
