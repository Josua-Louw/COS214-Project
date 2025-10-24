#ifndef CARESTRATEGY_H
#define CARESTRATEGY_H

/**
 * @file CareStrategy.h
 * @brief Declaration of the abstract CareStrategy class.
 *
 * @class CareStrategy
 * @brief Defines the interface for different plant care strategies.
 *
 * This abstract class represents the Strategy design pattern's interface.
 * Concrete care strategies implement this interface to provide customized behavior for plant maintenance.
 *
 * @note The Strategy pattern is used to encapsulate various plant care techniques and
 * allow dynamic selection of care behavior at runtime.
 */
class CareStrategy {

public:

    /**
     * @brief Applies the specific care behavior defined by the concrete strategy.
     *
     * @note This is a pure virtual function that must be overridden by subclasses.
     */
    virtual void applyCare() = 0;

    /**
     * @brief Retrieves the name or description of the applied care strategy.
     *
     * @note Used primarily for identifying the current strategy being applied.
     */
    virtual void getStrategyName() = 0;
};

#endif
