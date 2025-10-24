#include "PotAdapter.h"

std::string PotAdapter::getName() const {
    return pot->getName();
}

PotAdapter::~PotAdapter() {
    if (pot != nullptr)
    {
        delete pot;
    }
}
