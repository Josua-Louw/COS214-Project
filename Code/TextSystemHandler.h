#ifndef TEXTSYSTEMHANDLER_H
#define TEXTSYSTEMHANDLER_H

#include "SystemHandler.h"
#include <iostream>

class TextSystemHandler : public SystemHandler {
public:
    TextSystemHandler() : SystemHandler() {}
    ~TextSystemHandler() override = default;

    void systemMenue() override;
    //void addSection() override;
    void addPlant() override;
    void registerStaffMember() override;
    void processCustomerOrder() override;
};

#endif // TEXTSYSTEMHANDLER_H