#ifndef GUISYSTEMHANDLER_H
#define GUISYSTEMHANDLER_H

#include "SystemHandler.h"
#include "Window.h"
#include <string>

class GUISystemHandler : public SystemHandler {
public:
    GUISystemHandler();
    ~GUISystemHandler() override;
    void systemMenue() override;
    
    // Plant management
    void addPlant() override;
    void addPot();
    void addSeedPacket();
    void addDecoration();
    
    // Staff management
    void registerStaffMember() override;
    void registerPlantCaretaker();
    void registerSalesManager();
    void assignCareTask();
    void assignSaleTask();
    
    // Order processing
    void processCustomerOrder() override;
    void createOrder();
    void addPlantToOrder();
    void addPotToOrder();
    void addSeedToOrder();
    void addDecorationToOrder();
    
    // Greenhouse management
    void waterAllPlants();
    void fertilizeAllPlants();
    std::string getGreenhouseSummary();
    std::string getInventory();
    std::string getStaffInfo();

private:
    Window* m_window;
};

#endif