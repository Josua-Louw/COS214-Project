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
	double getPrice() const override;
	std::string getType() const override;
};

#endif
