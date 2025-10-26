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

    double getPrice() const;
    void expand(GreenHouse* gh) override;
    double sell(Item* item) override;
    GreenHouse* getSubsection(const std::string& sectionName) override;
    Iterator<Item*>* createIterator() override;
    Item* findItem(const std::string& itemName) override;
    void printSummary() const override;
    size_t getTotalItemCount() const;
    void printSummaryHelper(int indentLevel) const;
};

#endif // POTADAPTER_H