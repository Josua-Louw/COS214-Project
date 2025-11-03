#ifndef GUISYSTEMHANDLER_H
#define GUISYSTEMHANDLER_H

#include "SystemHandler.h"
#include "Window.h"
#include <string>
#include <utility>
#include "SellCommand.h"
#include "FertilizerBoostStrategy.h"
#include "WaterLimitingStrategy.h"
#include "RegularCareStrategy.h"

class GUISystemHandler : public SystemHandler {
public:
    GUISystemHandler();
    ~GUISystemHandler() override;
    void systemMenue() override;
    
    // Plant management
    void addPlant() override;
    
    // Staff management
    void registerStaffMember() override;
    
    // Order processing
    void processCustomerOrder() override;
    
    // Greenhouse management
    std::string getGreenhouseSummary();
    std::string getInventory();
    std::string getStaffInfo();

private:
    Window* m_window;
    std::vector<std::pair<std::string, double>> plantNames = {{"Rose Plant", 25.0}, {"Tulip Plant", 30.0}, {"Daisy Plant", 20.0}, {"Sunflower Plant", 15.0}, {"Orchid Plant", 40.0}, {"Lily Plant", 35.0}};
    std::vector<std::pair<std::string, double>> potNames = {{"Ceramic Pot", 15.0}, {"Plastic Pot", 10.0}, {"Terracotta Pot", 12.0}, {"Wooden Pot", 18.0}, {"Metal Pot", 20.0}};
    std::vector<std::pair<std::string, double>> seedNames = {{"Sunflower Seeds", 5.0}, {"Rose Seeds", 6.0}, {"Tulip Bulbs", 7.0}, {"Daisy Seeds", 4.0}, {"Orchid Seeds", 8.0}};
    std::vector<std::pair<std::string, double>> decorationNames = {{"Glitter Decoration", 8.0}, {"Fairy Lights", 10.0}, {"Mini Gnome", 12.0}, {"Decorative Stones", 6.0}, {"Plant Stakes", 5.0}};
    int customerIdCounter = 0;
    int staffIdCounter = 0;
    const std::vector<CareStrategy*> careStrategies = {new RegularCareStrategy(), new FertilizerBoostStrategy(), new WaterLimitingStrategy()};
};

#endif