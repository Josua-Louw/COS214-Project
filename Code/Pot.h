#ifndef POT_H
#define POT_H

#include "PlantDecorator.h"

/**
 * @file Pot.h
 * @brief This file contains the definition of the Pot class.
 */

 /**
  * @class Pot
  * @brief Represents a pot decoration for a plant.
  * Inherits from PlantDecorator.
  * Provides methods to get the price and type of the pot.
  */

class Pot : public PlantDecorator {
public:
	/**
	 * @brief Gets the price of the pot.
	 * @return The price of the pot as a double.
	 */
	double getPrice() const override;
	/**
	 * @brief Create a clone of the pot.
	 * @return A pointer to the newly created clone of the pot.
	 */
	PLANT_TYPE getType() const override;
};

#endif
