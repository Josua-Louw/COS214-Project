#include "SeedPacketAdapter.h"

std::string SeedPacketAdapter::getName() const {
    return seedPacket->getName();
}

SeedPacketAdapter::~SeedPacketAdapter() {
    if (seedPacket != nullptr)
    {
        delete seedPacket;
    }
}   