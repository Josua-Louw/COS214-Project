#include "SeedPacketAdapter.h"
#include "ItemIterator.h"

std::string SeedPacketAdapter::getName() const {
    return seedPacket->getName();
}

double SeedPacketAdapter::getPrice() const {
    return seedPacket->getPrice();
}

SeedPacketAdapter::~SeedPacketAdapter() {
    if (seedPacket != nullptr)
    {
        delete seedPacket;
    }
}

PLANT_TYPE SeedPacketAdapter::getType() const {
    return seedPacket->getType();
}