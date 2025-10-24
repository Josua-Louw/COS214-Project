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