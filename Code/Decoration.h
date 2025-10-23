#ifndef DECORATION_H
#define DECORATION_H

#include "PlantDecorator.h"

/**
 * @file Decoration.h
 * @brief This file contains the definition of the Decoration class.
 */

 /**
  * @class Decoration
  * @brief Represents a decoration for a plant.
  * Inherits from PlantDecorator.
  * Provides methods to get the price and type of the decoration.
  */

class Decoration : public PlantDecorator {
public:
	/**
	 * @brief Gets the price of the decoration.
	 * @return The price of the decoration as a double.
	 */
	double getPrice() const override;

	/**
	 * @brief Gets the type of the decoration.
	 * @return The type of the decoration as a string.
	 */
	PLANT_TYPE getType() const override;
};

#endif
