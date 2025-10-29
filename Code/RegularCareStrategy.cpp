#include "RegularCareStrategy.h"
#include "GreenHousePlant.h"

/**
 * @file RegularCareStrategy.cpp
 * @brief Implementation of the RegularCareStrategy class.
 *
 * Defines the behavior for plants that receive consistent and balanced care routines.
 */

/**
 * @brief Applies the standard care routine for a plant.
 *
 * @note Includes balanced watering, nutrient checks and all other overall maintenance.
 */
std::vector<CommandPtr> RegularCareStrategy::applyCare(GreenHousePlant& plant) {
	if (!plant.getIsAlive()) {
		return {};
	}
	plant.setWaterSuccess(false);
	plant.setFertilizingSuccess(false);
	plant.setWaterBusy(false);
	plant.setFertilizingBusy(false);
	CommandPtr returnWater = plant.water(4);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	CommandPtr returnFeed = plant.feed(4);
	return { returnWater, returnFeed};
}

/**
 * @brief Returns the identifying name of this strategy.
 *
 * @return The name of the care strategy ("Regular Care Strategy").
 */
std::string RegularCareStrategy::getStrategyName() const {
	return "RegularCare";
}
