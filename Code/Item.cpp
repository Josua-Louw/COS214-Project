#include "Item.h"
#include "ItemIterator.h"

void Item::expand(GreenHouse* gh) {
    //N.A only for composites
}

double Item::sell(Item* item) {
    return getPrice();
}

GreenHouse* Item::getSubsection(const std::string&) {
   return nullptr;
}

Iterator<Item*>* Item::createIterator() {
    return new ItemIterator(std::vector<Item*>{});
}

Item* Item::findItem(const std::string& itemName) {
    return itemName == getName() ? this : nullptr;
}

void Item::printSummary() const {
    std::cout << "Item Summary: " << getName() << ", Price: " << getPrice() << std::endl;
}

size_t Item::getTotalItemCount() const {
    return 0;
}

void Item::printSummaryHelper(int indentLevel) const {
    //N.A. Only for composites
}