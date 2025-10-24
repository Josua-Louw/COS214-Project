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
  * Provides method to get the type of the plant.
  */

class PlantType : public PlantDecorator {
public:
	/**
	 * @brief Constructor for PlantType.
	 * @param plant Pointer to the OrderPlant object to be decorated.
	 */
	PlantType(OrderPlant* plant);
	~PlantType();
	/**
	 * @brief Get the type of the plant.
	 * @return The type of the plant as a string.
	 */
	std::string getType() const override;
};

#endif
