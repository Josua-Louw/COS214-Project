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


void SeedPacketAdapter::expand(GreenHouse* gh) {
    //N.A
}

double SeedPacketAdapter::sell(Item* item) {
    return 0.0;
}

GreenHouse* SeedPacketAdapter::getSubsection(const std::string&) {
    return nullptr;
}

Iterator<Item*>* SeedPacketAdapter::createIterator() {
    return new ItemIterator(std::vector<Item*>{});
}

Item* SeedPacketAdapter::findItem(const std::string& itemName) {
    return nullptr;
}

void SeedPacketAdapter::printSummary() const {
    //N.A
}

size_t SeedPacketAdapter::getTotalItemCount() const {
    return 0;
}

void SeedPacketAdapter::printSummaryHelper(int indentLevel) const {

}