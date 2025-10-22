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
	PlantType(OrderPlant* plant);
	~PlantType();
	std::string getType() const override;
};

#endif
