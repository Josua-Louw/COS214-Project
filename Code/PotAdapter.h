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
    PotAdapter(Pot* p) : pot(p) {}
    std::string getName() const override;
    ~PotAdapter();
};

#endif // POTADAPTER_H