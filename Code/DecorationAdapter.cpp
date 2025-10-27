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

PLANT_TYPE DecorationAdapter::getType() const {
    return decoration->getType();
}