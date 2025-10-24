#include "PotAdapter.h"
#include "ItemIterator.h"

std::string PotAdapter::getName() const {
    return pot->getName();
}

double PotAdapter::getPrice() const {
    return pot->getPrice();
}

PotAdapter::~PotAdapter() {
    if (pot != nullptr)
    {
        delete pot;
    }
}

void PotAdapter::expand(GreenHouse* gh) {
    //N.A
}

double PotAdapter::sell(Item* item) {
    return 0.0;
}

GreenHouse* PotAdapter::getSubsection(const std::string&) {
   return nullptr;
}

Iterator<Item*>* PotAdapter::createIterator() {
    return new ItemIterator(std::vector<Item*>{});
}

Item* PotAdapter::findItem(const std::string& itemName) {
    return nullptr;
}

void PotAdapter::printSummary() const {
    //N.A
}

size_t PotAdapter::getTotalItemCount() const {
    return 0;
}

void PotAdapter::printSummaryHelper(int indentLevel) const {

}