#ifndef SEED_PACKET_ADAPTER_H
#define SEED_PACKET_ADAPTER_H

#include "SeedPacket.h"
#include "Item.h"

/**
 * @file SeedPacketAdapter.h
 * @brief This file contains the definition of the SeedPacketAdapter class.
 */

/**
 * @class SeedPacketAdapter
 * @brief Adapter class to adapt SeedPacket to Item interface.
 */

class SeedPacketAdapter : public Item {
private:
    SeedPacket* seedPacket;
public:
    SeedPacketAdapter(SeedPacket* sp) : seedPacket(sp) {}
    std::string getName() const override;
    ~SeedPacketAdapter();
};

#endif // SEED_PACKET_ADAPTER_H