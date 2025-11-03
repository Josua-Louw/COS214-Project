#include "Plant.h"
#include "ItemIterator.h"
#include <iostream>

#include "PlantMaker.h"

Plant::Plant()
     : implementor(nullptr) {
    // default left intentionally null
}

Plant::Plant(PlantImplementor* impl) 
     : implementor(impl) {

}

Plant::Plant(const std::string& name, double price, NurseryMediator* mediator, CareStrategy* care, PlantMaker* maker)
{
    implementor = maker->makePlant(name, price, mediator, care);
}

Plant::Plant(const std::string& name, double price, PlantMaker* maker)
{
    implementor = maker->makePlant(name,price,nullptr,nullptr);
}

void Plant::convertToOrderType()
{
    if (implementor) {
        std::string name = implementor->getName();
        double price = implementor->getPrice();
        if (implementor->getType() == PLANT_TYPE::GREENHOUSE_PLANT) 
        {
            GreenHousePlant* ghPlant = dynamic_cast<GreenHousePlant*>(implementor);
            if (ghPlant) {
                ghPlant->deactivatePlant();
            }
            implementor = new PlantType(price, name);
            std::cout << "Plant converted to OrderPlant type: " << name << std::endl;
        }
    } else {
        implementor = new PlantType(0.0, "Unnamed Plant");
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
        if (implementor->getType() == PLANT_TYPE::GREENHOUSE_PLANT)
        {
            GreenHousePlant* ghPlant = dynamic_cast<GreenHousePlant*>(implementor);
            if (ghPlant) {
                ghPlant->deactivatePlant();
            }
        } else {
            delete implementor;
            implementor = nullptr;
        }
    }
}

OrderPlant* Plant::getOrderPlant() const {
    if (implementor)
    {
        if (implementor->getType() == PLANT_TYPE::GREENHOUSE_PLANT)
        {
            // Convert GreenHousePlant to PlantType for OrderPlant
            std::string name = implementor->getName();
            double price = implementor->getPrice();
            PlantType tempPlantType(price, name);
            return dynamic_cast<OrderPlant*>(tempPlantType.clone());
        } else {
            return dynamic_cast<OrderPlant*>(implementor->clone());
        }
    }
    return nullptr;
}
