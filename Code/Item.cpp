#include "Item.h"
#include "ItemIterator.h"

void Item::expand(GreenHouse* gh) {
    //N.A
}

double Item::sell(Item* item) {
    return 0.0;
}

GreenHouse* Item::getSubsection(const std::string&) {
   return nullptr;
}

Iterator<Item*>* Item::createIterator() {
    return new ItemIterator(std::vector<Item*>{});
}

Item* Item::findItem(const std::string& itemName) {
    return nullptr;
}

void Item::printSummary() const {
    //N.A
}

size_t Item::getTotalItemCount() const {
    return 0;
}

void Item::printSummaryHelper(int indentLevel) const {

}