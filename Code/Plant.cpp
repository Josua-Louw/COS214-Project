#include "Plant.h"
#include "ItemIterator.h"
#include <iostream>

Plant::Plant()
     : implementor(nullptr) {
    // default left intentionally null
}

Plant::Plant(PlantImplementor* impl) 
     : implementor(impl) {

}

Plant::Plant(const std::string& name, double price, NurseryMediator* mediator, CareStrategy* care) 
{
    implementor = new GreenHousePlant(name, price, mediator, care);
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

OrderPlant* Plant::getOrderPlant() const {
    if (implementor)
    {
        if (getType() == PLANT_TYPE::GREENHOUSE_PLANT)
        {
            // Convert GreenHousePlant to PlantType for OrderPlant
            std::string name = implementor->getName();
            double price = implementor->getPrice();
            PlantType tempPlantType(price, name);
            return dynamic_cast<OrderPlant*>(tempPlantType.clone());
        }
        return dynamic_cast<OrderPlant*>(implementor->clone());
    }
    return nullptr;
}
