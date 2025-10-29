#ifndef GUISYSTEMHANDLER_H
#define GUISYSTEMHANDLER_H

#include "SystemHandler.h"
#include "Window.h"

class GUISystemHandler : public SystemHandler {
public:
    GUISystemHandler();
    ~GUISystemHandler() override;
    void systemMenue() override;
    void addPlant() override;
    void registerStaffMember() override;
    void processCustomerOrder() override;
};

#endif