#ifndef SYSTEMHANDLER_H
#define SYSTEMHANDLER_H

#include "GreenHouse.h"
#include "Section.h"
#include "NurseryHub.h"
#include "Plant.h"
#include "PotAdapter.h"
#include "SeedPacketAdapter.h"
#include "DecorationAdapter.h"
#include "PlantCaretaker.h"
#include "SalesManager.h"

class SystemHandler {
protected:
    NurseryHub* nurseryHub;
    GreenHouse* greenHouse;
public:
    SystemHandler() {
        nurseryHub = new NurseryHub();
        greenHouse = new Section("GreenHouse", 5);
        systemMenue();
    };
    virtual ~SystemHandler() {
        delete nurseryHub;
        delete greenHouse;
    };
    virtual void systemMenue() = 0;
    virtual void addSection() = 0;
    virtual void addPlant() = 0;
    virtual void registerStaffMember() = 0;
    virtual void processCustomerOrder() = 0;
};

#endif // SYSTEMHANDLER_H
