#ifndef SEEDS_H
#define SEEDS_H
/**
* @file Seeds.h
* @brief This file contains the definition of the Seeds class.
*/

/**
* @class Seeds
* @brief Represents the seeds of the particular plant.
*/
class Seeds : Plant {

public:

	/**
	* @brief Gets the price of the seeds.
	* @return The price of the seeds as a double.
	*/
	double getPrice();

	/**
	* @brief Create a clone of the seeds.
	* @return A pointer to the newly created clone of the seeds.
	*/
	Plant* clone();

	/**
	* @brief Get the type of plant the seeds are of.
	* @return The type of plant the seeds are of as a string.
	*/
	string getType();
};

#endif
