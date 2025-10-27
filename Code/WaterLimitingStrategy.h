#ifndef WATERLIMITINGSTRATEGY_H
#define WATERLIMITINGSTRATEGY_H

#include <vector>

#include "CareStrategy.h"
#include "Command.h"
/**
 * @file WaterLimitingStrategy.h
 * @brief Declaration of the concrete WaterLimitingStrategy class.
 *
 * @class WaterLimitingStrategy
 * @brief Represents a care strategy that limits water intake to strengthen the plant.
 *
 * This strategy is used for plants that require reduced watering intervals
 * to improve root strength or prepare for specific growth phases.
 *
 * @note Implements the Strategy design pattern.
 */
class WaterLimitingStrategy : public CareStrategy {


public:
	/**
	 * @brief Applies limited watering to the plant.
	 *
	 * @note Used for plants that thrive under controlled water conditions.
	 */
	std::vector<Command*> applyCare(GreenHousePlant& plant) override;

	/**
	 * @brief Returns the identifying name of this strategy ("Water Limiting Strategy").
	 */
	std::string getStrategyName() const override;
};

#endif
