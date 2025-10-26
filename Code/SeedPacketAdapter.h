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

    double getPrice() const;
    void expand(GreenHouse* gh) override;
    double sell(Item* item) override;
    GreenHouse* getSubsection(const std::string& sectionName) override;
    Iterator<Item*>* createIterator() override;
    Item* findItem(const std::string& itemName) override;
    void printSummary() const override;
    size_t getTotalItemCount() const;
    void printSummaryHelper(int indentLevel) const;
};

#endif // SEED_PACKET_ADAPTER_H