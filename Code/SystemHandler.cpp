#include "SystemHandler.h"

SystemHandler::SystemHandler() {
    nurseryHub = new NurseryHub();
    greenHouse = new Section("GreenHouse", 5);
};

SystemHandler::~SystemHandler() {
    delete nurseryHub;
    delete greenHouse;
};