#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

#include "Plant.h"

/**
* @file PlantDecorator.h
* @brief This file contains the definition of the PlantDecorator class.
*/

/**
* @class PlantDecorator
* @brief Abstract base class representing a plant decorator.
*/
class PlantDecorator : public Plant {

public:

	/**
	* @brief Gets the price of the decorated plant.
	* @return The price of the decorated plant as a double.
	*/
	double getPrice();

	/**
	* @brief Create a clone of the decorated plant.
	* @return A pointer to the newly created clone of the decorated plant.
	*/
	Plant* clone();

private:

	/**
	* @brief Pointer to the component being decorated.
	*/
	Plant* component;

};

#endif
