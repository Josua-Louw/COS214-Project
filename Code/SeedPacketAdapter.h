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
    /**
     * @brief Constructor for SeedPacketAdapter.
     * @details Initializes with a new SeedPacket instance.
     */
    SeedPacketAdapter(std::string name, double price) : seedPacket(new SeedPacket(price, name)) {}
    /**
     * @brief Constructor for SeedPacketAdapter.
     * @param sp Pointer to the SeedPacket object to be adapted.
     */
    SeedPacketAdapter(SeedPacket* sp) : seedPacket(sp) {}
    /**
     * @brief Gets the name of the seed packet.
     * @return The name of the seed packet as a string.
     */
    std::string getName() const override;
    /**
     * @brief Destructor for SeedPacketAdapter.
     */
    ~SeedPacketAdapter();

    double getPrice() const override;
    PLANT_TYPE getType() const override;
};

#endif // SEED_PACKET_ADAPTER_H