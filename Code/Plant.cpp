#include "Plant.h"
#include "ItemIterator.h"
#include <iostream>

Plant::Plant()
     : implementor(nullptr) {
    // default left intentionally null (caller can attach implementor later)
}

Plant::Plant(PlantImplementor* impl) 
     : implementor(impl) {

}

void Plant::convertToOrderType()
{

}

double Plant::getPrice() const
{
    if (implementor) return implementor->getPrice();
    return 0.0;
}

std::string Plant::getImplementorType()
{
    if (!implementor) return "None";
    return "Implementor"; //generic
}

std::string Plant::getName() const
{
    if (implementor) return implementor->getName();
    return std::string("Unnamed Plant");
}

Plant::~Plant()
{
    if (implementor) {
        delete implementor;
        implementor = nullptr;
    }
}

void Plant::expand(GreenHouse* gh) {
    (void)gh;
}

double Plant::sell(Item* item) {
    (void)item;
    return getPrice();
}

GreenHouse* Plant::getSubsection(const std::string&) {
   return nullptr;
}

Iterator<Item*>* Plant::createIterator() {
   return new ItemIterator(std::vector<Item*>{});
}

Item* Plant::findItem(const std::string& itemName) {
    if (getName() == itemName) return const_cast<Plant*>(this);
    return nullptr;
}

void Plant::printSummary() const {
    std::cout << "Plant: " << getName() << " (R" << getPrice() << ")" << std::endl;
}

size_t Plant::getTotalItemCount() const {
    return 0;
}

void Plant::printSummaryHelper(int indentLevel) const {

}

