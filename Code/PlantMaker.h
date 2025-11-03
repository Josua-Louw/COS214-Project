//
// Created by darius on 2025/11/03.
//

#ifndef COS214_PROJECT_PLANTMAKER_H
#define COS214_PROJECT_PLANTMAKER_H
#include <vector>

#include "GreenHousePlant.h"



class PlantMaker {
private:
    std::vector<GreenHousePlant*> plants{};
public:
    PlantMaker() = default;
    ~PlantMaker();

    GreenHousePlant * makePlant(std::string name, double price, NurseryMediator * mediator, CareStrategy * care);

};


#endif //COS214_PROJECT_PLANTMAKER_H