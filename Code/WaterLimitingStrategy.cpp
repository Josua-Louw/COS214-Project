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
void WaterLimitingStrategy::applyCare(GreenHousePlant& plant) {
	plant.adjustHydration(+1);
	plant.adjustNutrition(+2);
	plant.setTimeForNextCare(10); //(vir nou n placeholder)replace met timers of ticks later saam Darius
}

/**
 * @brief Returns the identifying name of this strategy.
 *
 * @return The name of the care strategy ("Water Limiting Strategy").
 */
std::string WaterLimitingStrategy::getStrategyName() const {
	return "WaterLimiting";
}
