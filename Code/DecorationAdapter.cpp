#include "DecorationAdapter.h"
#include "ItemIterator.h"

std::string DecorationAdapter::getName() const {
    return decoration->getName();
}

double DecorationAdapter::getPrice() const {
    return decoration->getPrice();
}

DecorationAdapter::~DecorationAdapter() {
    if (decoration != nullptr)
    {
        delete decoration;
    }
}

void DecorationAdapter::expand(GreenHouse* gh) {
    //N.A
}

double DecorationAdapter::sell(Item* item) {
    return 0.0;
}

GreenHouse* DecorationAdapter::getSubsection(const std::string&) {
   return nullptr;
}

Iterator<Item*>* DecorationAdapter::createIterator() {
   return new ItemIterator(std::vector<Item*>{});
}

Item* DecorationAdapter::findItem(const std::string& itemName) {
    return nullptr;
}

void DecorationAdapter::printSummary() const {
    //N.A
}

size_t DecorationAdapter::getTotalItemCount() const {
    return 0;
}

void DecorationAdapter::printSummaryHelper(int indentLevel) const {

}