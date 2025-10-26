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
  * Provides methods to get type of the pot and clone the pot.
  */

class Pot : public PlantDecorator {
public:
	Pot() : PlantDecorator() {}
	Pot(double cost, const std::string& name) : PlantDecorator(cost, name) {}
	Pot(const Pot& other) : PlantDecorator(other) {}

	/**
	 * @brief Get the type of the pot.
	 * @return The type of the pot as a PLANT_TYPE enum value.
	 */
	PLANT_TYPE getType() const override;
	/**
	 * @brief Creates a clone of the Pot.
	 * @return A pointer to the cloned Pot.
	 */
	PlantImplementor* clone() override;
};

#endif
