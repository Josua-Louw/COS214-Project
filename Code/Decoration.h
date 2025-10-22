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
	double getPrice() const override;

	std::string getType() const override;
};

#endif
