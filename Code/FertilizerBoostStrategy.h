#ifndef FERTILIZERBOOSTSTRATEGY_H
#define FERTILIZERBOOSTSTRATEGY_H

#include <vector>

#include "CareStrategy.h"
#include "Command.h"
#include <memory>
using CommandPtr = std::shared_ptr<Command>;
/**
 * @file FertilizerBoostStrategy.h
 * @brief Declaration of the concrete FertilizerBoostStrategy class.
 *
 * @class FertilizerBoostStrategy
 * @brief Represents a care strategy that enhances plant growth through application of fertilizer.
 *
 * This class is a concrete implementation of the CareStrategy interface. It defines
 * how plants should be treated when a fertilizer boost is applied as part of their care strategy.
 *
 * @note Implements the Strategy design pattern.
 */

class FertilizerBoostStrategy : public CareStrategy {
public:
	/**
	 * @brief Applies fertilizer care to the plant.
	 *
	 * @note This method defines how the plant receives fertilizer to promote healthy growth.
	 */
	std::vector<CommandPtr> applyCare(GreenHousePlant& plant) override;

	/**
	 * @brief Returns the name of this strategy ("Fertilizer Boost Strategy").
	 */
	std::string getStrategyName() const override;
};

#endif
