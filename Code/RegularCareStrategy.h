#ifndef REGULARCARESTRATEGY_H
#define REGULARCARESTRATEGY_H

/**
 * @file RegularCareStrategy.h
 * @brief Declaration of the concrete RegularCareStrategy class.
 *
 * @class RegularCareStrategy
 * @brief Represents a standard care strategy that provides consistent maintenance to plants.
 *
 * This class implements the CareStrategy interface and defines how a plant is cared for
 * under regular/normal conditions, such as regular watering and sunlight exposure.
 *
 * @note Implements the Strategy design pattern.
 */
class RegularCareStrategy : CareStrategy {


public:
	/**
	 * @brief Applies regular care actions to maintain plant health.
	 *
	 * @note Represents a balanced and consistent care approach.
	 */
	void applyCare();

	/**
	 * @brief Returns the identifying name of this strategy ("Regular Care Strategy").
	 */
	void getStrategyName();
};

#endif
