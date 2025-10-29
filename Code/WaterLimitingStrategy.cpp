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
std::vector<CommandPtr> WaterLimitingStrategy::applyCare(GreenHousePlant& plant) {
    if (!plant.getIsAlive()) {
        return {};
    }
    plant.setWaterSuccess(false);
    plant.setFertilizingSuccess(false);
    plant.setWaterBusy(false);
    plant.setFertilizingBusy(false);
    CommandPtr returnWater = plant.water(2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    CommandPtr returnFeed = plant.feed(4);
    return { returnWater, returnFeed};
}

/**
 * @brief Returns the identifying name of this strategy.
 *
 * @return The name of the care strategy ("Water Limiting Strategy").
 */
std::string WaterLimitingStrategy::getStrategyName() const {
	return "WaterLimiting";
}
