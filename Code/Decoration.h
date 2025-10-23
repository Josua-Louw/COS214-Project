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
	Decoration() : PlantDecorator() {}
	Decoration(double cost, const std::string& name) : PlantDecorator(cost, name) {}
	Decoration(const Decoration& other) : PlantDecorator(other) {}

	/**
	 * @brief Gets the type of the decoration.
	 * @return The type of the decoration as a string.
	 */
	PLANT_TYPE getType() const override;

	/**
	 * @brief Creates a clone of the Decoration.
	 * @return A pointer to the cloned Decoration.
	 */
	PlantImplementor* clone() override;
};

#endif
