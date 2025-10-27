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

Plant::Plant(const std::string& name, double price) 
{
    implementor = new GreenHousePlant(name, price);
}

void Plant::convertToOrderType()
{
    if (implementor) {
        std::string name = implementor->getName();
        double price = implementor->getPrice();
        delete implementor;
        implementor = new PlantType(price, name);
    }
}

double Plant::getPrice() const
{
    if (implementor) return implementor->getPrice();
    return 0.0;
}

PLANT_TYPE Plant::getType() const
{
    if (!implementor) return PLANT_TYPE::GREENHOUSE_PLANT;
    return implementor->getType();
}

PLANT_TYPE Plant::getType() const {
    if (implementor)
        return implementor->getType();
    return PLANT_TYPE::GREENHOUSE_PLANT; //safe default (in case)
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

