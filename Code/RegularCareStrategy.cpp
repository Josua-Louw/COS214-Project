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
std::vector<Command*> RegularCareStrategy::applyCare(GreenHousePlant& plant) {
	plant.setSuccess(false);
	plant.setBusy(false);
	Command* returnWater = plant.water(2);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	Command* returnFeed = plant.feed(2);
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
