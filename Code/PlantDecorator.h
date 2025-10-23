#ifndef PLANTDECORATOR_H
#define PLANTDECORATOR_H

#include "OrderPlant.h"

/**
* @file PlantDecorator.h
* @brief This file contains the definition of the PlantDecorator class.
*/

/**
* @class PlantDecorator
* @brief Abstract base class representing a plant decorator.
*/
class PlantDecorator : public OrderPlant {
public:
	PlantDecorator() : component(nullptr) {}
	PlantDecorator(double cost, const std::string& name) : OrderPlant(cost, name), component(nullptr) {}
	/**
	 * @brief Copy constructor.
	 * @param other The PlantDecorator object to copy from.
	 * @return A new PlantDecorator object that is a copy of the given object.
	 * @note This is a deep copy constructor.
	 */
	PlantDecorator(const PlantDecorator& other) : OrderPlant(other), component((other.component) ? dynamic_cast<OrderPlant*>(other.component->clone()) : nullptr) {}
	/**
	* @brief Gets the price of the decorated plant.
	* @return The price of the decorated plant as a double.
	* @note If there is a component, the price is the sum of the decorator's cost and the component's price.
	* @note If there is no component, the price is just the decorator's cost.
	*/
	double getPrice() const override;

	/**
	* @brief Add decoration to the given plant.
	* @param orderPlant Pointer to the plant to be decorated.
	* @return void.
	* @throws const char* if attempting to add more than one seed packet decoration.
	* @warning This function requires heap-allocated OrderPlant objects to function correctly.
	*/
	void decorate(OrderPlant* orderPlant) override;

	/**
	 * @brief Virtual destructor to ensure proper cleanup.
	 * @note Deletes the component if it exists.
	 */
	virtual ~PlantDecorator();

private:

	/**
	* @brief Pointer to the component being decorated.
	*/
	OrderPlant* component;

};

#endif
