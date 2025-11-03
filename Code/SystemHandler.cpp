#include "SystemHandler.h"

SystemHandler::SystemHandler() {
    nurseryHub = new NurseryHub();
    greenHouse = new Section("GreenHouse", 5);
    plantMaker = new PlantMaker();
};

SystemHandler::~SystemHandler() {
    delete nurseryHub;
    delete greenHouse;
    delete plantMaker;
};