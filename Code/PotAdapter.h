#ifndef POTADAPTER_H
#define POTADAPTER_H

#include "Pot.h"
#include "Item.h"

/**
 * @file PotAdapter.h
 * @brief This file contains the definition of the PotAdapter class.
 */

 /**
  * @class PotAdapter
  * @brief Adapter class to adapt Pot to Item interface.
  */

class PotAdapter : public Item {
private:
    Pot* pot;

public:
    /**
     * @brief Constructor for PotAdapter.
     * @details Initializes with a new Pot instance.
     */
    PotAdapter(std::string name, double price) : pot(new Pot(price, name)) {}
    /**
     * @brief Constructor for PotAdapter.
     * @param p Pointer to the Pot object to be adapted.
     */
    PotAdapter(Pot* p) : pot(p) {}
    /**
     * @brief Gets the name of the pot.
     * @return The name of the pot as a string.
     */
    std::string getName() const override;
    /**
     * @brief Destructor for PotAdapter.
     */
    ~PotAdapter();

    double getPrice() const override;

    PLANT_TYPE getType() const override;

    OrderPlant* getOrderPlant() const override;
};

#endif // POTADAPTER_H