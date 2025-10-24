#ifndef SEED_PACKET_H
#define SEED_PACKET_H

#include "OrderPlant.h"

/**
* @file SeedPacket.h
* @brief This file contains the definition of the SeedPacket class.
*/

/**
* @class SeedPacket
* @brief Represents the seeds of the particular plant.
*/
class SeedPacket : public OrderPlant {

public:

	/**
	* @brief Gets the price of the seeds.
	* @return The price of the seeds as a double.
	*/
	double getPrice() const;

	std::string getName() const;

	/**
	* @brief Create a clone of the seeds.
	* @return A pointer to the newly created clone of the seeds.
	*/
	PlantImplementor* clone();

	/**
	* @brief Get the type of plant the seeds are of.
	* @return The type of plant the seeds are of as a string.
	*/
	std::string getType() const;

	void decorate(OrderPlant* orderPlant);
};

#endif
