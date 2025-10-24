#ifndef PLANTTYPE_H
#define PLANTTYPE_H

#include "PlantDecorator.h"

/**
 * @file PlantType.h
 * @brief This file contains the definition of the PlantType class.
 */

 /**
  * @class PlantType
  * @brief Represents the type of a plant.
  * Inherits from PlantDecorator.
  * Provides method to get the type of the plant and clone the plant type.
  */

class PlantType : public PlantDecorator {
public:
	PlantType() : PlantDecorator() {}
	PlantType(double cost, const std::string& name) : PlantDecorator(cost, name) {}
	PlantType(const PlantType& other) : PlantDecorator(other) {}

	/**
	 * @brief Gets the type of the plant.
	 * @return The type of the plant as a PLANT_TYPE enum value.
	 */
	PLANT_TYPE getType() const override;
	/**
	 * @brief Creates a clone of the PlantType.
	 * @return A pointer to the cloned PlantType.
	 */
	PlantImplementor* clone() override;
};

#endif
