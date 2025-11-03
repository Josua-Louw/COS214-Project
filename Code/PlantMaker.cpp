//
// Created by darius on 2025/11/03.
//

#include "PlantMaker.h"

PlantMaker::~PlantMaker()  {
    for (auto plant : plants) {
        if (plant) {
            std::cout << "Deleting plant: " << plant->getName() << "\n";
            delete plant;
            plant = nullptr;
        }
    }
    std::cout << "All plants deleted\n";
}


GreenHousePlant * PlantMaker::makePlant(std::string name, double price, NurseryMediator * mediator, CareStrategy * care) {
    auto* plant = new GreenHousePlant(name,price,mediator,care,this);
    plants.push_back(plant);
    return plant;
}
