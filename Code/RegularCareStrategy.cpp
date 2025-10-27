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
void RegularCareStrategy::applyCare(GreenHousePlant& plant) {
    plant.adjustHydration(+3);
    plant.adjustNutrition(+2);
    plant.setTimeForNextCare(8); //(vir nou n placeholder)replace met timers of ticks later saam Darius
}

/**
 * @brief Returns the identifying name of this strategy.
 *
 * @return The name of the care strategy ("Regular Care Strategy").
 */
std::string RegularCareStrategy::getStrategyName() const {
	return "RegularCare";
}
