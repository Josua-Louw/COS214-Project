#include "DecorationAdapter.h"

std::string DecorationAdapter::getName() const {
    return decoration->getName();
}

DecorationAdapter::~DecorationAdapter() {
    if (decoration != nullptr)
    {
        delete decoration;
    }
}