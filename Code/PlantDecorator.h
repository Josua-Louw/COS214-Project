#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

#include "OrderPlant.h"

/**
* @file PlantDecorator.h
* @brief This file contains the definition of the PlantDecorator class.
*/

/**
* @class PlantDecorator
* @brief Abstract base class representing a plant decorator.
*/
class PlantDecorator : public OrderPlant {

public:

	/**
	* @brief Gets the price of the decorated plant.
	* @return The price of the decorated plant as a double.
	*/
	double getPrice() const override;

	/**
	* @brief Creates a clone of the PlantDecorator.
	* @return A pointer to the cloned PlantDecorator.
	*/
	PlantImplementor* clone() override;

	/**
	* @brief Add decoration to the given plant.
	* @param orderPlant Pointer to the plant to be decorated.
	* @return void.
	*/
	void decorate(OrderPlant* orderPlant) override;

private:

	/**
	* @brief Pointer to the component being decorated.
	*/
	OrderPlant* component;

};

#endif
