#ifndef PLANT_H
#define PLANT_H
/**
* @file Plant.h
* @brief This file contains the definition of the Plant class.
*/

/**
* @class Plant
* @brief Abstract base class representing the plant.
*/
class Plant : GreenHouse {

private:

	/**
	* @brief Pointer to the care startegy associated with this plant.
	*/
	CareStrategy* strategy;

	/**
	* @brief Pointer to the state the plant is currently in its lifecycle.
	*/
	PlantState* state;

	/**
	* @brief Name of the plant.
	*/
	string name;

public:

	/**
	* @brief Water the plant.
	*/
	virtual void water() = 0;

	/**
	* @brief Feed the plant.
	*/
	virtual void feed() = 0;

	/**
	* @brief Get the price of the plant.
	* @return The price of the plant as a double.
	*/
	virtual double getPrice() = 0;

	/**
	* @brief Create a clone of the plant.
	* @return A pointer to the newly created clone of the plant.
	*/
	virtual Plant* clone() = 0;

	/**
	* @brief Get the name of the plant.
	* @return The name of the plant as a string.
	*/
	string getName();

	/**
	* @brief Get the type of the plant.
	* @return The type of the plant as a string.
	*/
	virtual string getType() = 0;
};

#endif
