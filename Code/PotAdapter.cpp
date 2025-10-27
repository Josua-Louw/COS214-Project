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