#ifndef DECORATIONADAPTER_H
#define DECORATIONADAPTER_H

#include "Decoration.h"
#include "Item.h"

/**
 * @file DecorationAdapter.h
 * @brief This file contains the definition of the DecorationAdapter class.
 */

 /**
  * @class DecorationAdapter
  * @brief Adapter class to adapt Decoration to Item interface.
  */

class DecorationAdapter : public Item {
private:
    Decoration* decoration;
public:
    DecorationAdapter(Decoration* d) : decoration(d) {}
    std::string getName() const override;
    ~DecorationAdapter();
    
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

#endif // DECORATIONADAPTER_H
