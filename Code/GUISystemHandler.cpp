#include "GUISystemHandler.h"
#include <iostream>
#include <sstream>

GUISystemHandler::GUISystemHandler() : m_window(nullptr) {
    // Initialize system components
    greenHouse = new Section("Main Greenhouse", 100);
    nurseryHub = new NurseryHub();
    nurseryHub->setInventoryRoot(greenHouse);
    customerIdCounter = 0;
    staffIdCounter = 0;
}

GUISystemHandler::~GUISystemHandler() {
    delete m_window;
    delete greenHouse;
    delete nurseryHub;
}

void GUISystemHandler::systemMenue() {
    auto app = Gtk::Application::create("org.greenhouse.management");
    m_window = new Window(this);
    app->run(*m_window);
}

// Plant Management
void GUISystemHandler::addPlant() {
    std::cout << "Adding item to greenhouse" << std::endl;
    switch ( m_window->getAddPlantState())
    {
    case addPlantState::PLANT:
    {
        int index = rand() % plantNames.size();
        std::string plantName = plantNames[index].first;
        double plantPrice = plantNames[index].second;
        Plant* newPlant = new Plant(plantName, plantPrice);
        greenHouse->expand(newPlant);
        break;
    }
    case addPlantState::POT:
    {
        int potIndex = rand() % potNames.size();
        std::string potName = potNames[potIndex].first;
        double potPrice = potNames[potIndex].second;
        PotAdapter* newPot = new PotAdapter(potName, potPrice);
        greenHouse->expand(newPot);
        break;
    }
    case addPlantState::SEED:
    {
        int seedIndex = rand() % seedNames.size();
        std::string seedName = seedNames[seedIndex].first;
        double seedPrice = seedNames[seedIndex].second;
        SeedPacketAdapter* newSeed = new SeedPacketAdapter(seedName, seedPrice);
        greenHouse->expand(newSeed);
        break;
    }
    case addPlantState::DECORATION:
    {
        int decorIndex = rand() % decorationNames.size();
        std::string decorName = decorationNames[decorIndex].first;
        double decorPrice = decorationNames[decorIndex].second;
        DecorationAdapter* newDecor = new DecorationAdapter(decorName, decorPrice);
        greenHouse->expand(newDecor);
        break;
    }
    default:
        break;
    }
    
}

// Staff Management
void GUISystemHandler::registerStaffMember() {
    // Default implementation
    std::cout << "Registering staff member" << std::endl;
    switch (m_window->getRegisterStaffState())
    {
    case registerStaffState::PLANT_CARETAKER:
        {
            std::string id = "Plant Caretaker:" + std::to_string(++staffIdCounter);
            PlantCaretaker* caretaker = new PlantCaretaker(id, nurseryHub);
            nurseryHub->registerStaff(caretaker);
        }
        break;
    case registerStaffState::SALES_MANAGER:
        {
            std::string id = "Sales Manager:" + std::to_string(++staffIdCounter);
            SalesManager* manager = new SalesManager(id, nurseryHub);
            nurseryHub->registerStaff(manager);
        }
        break;
    default:
        break;
    }
}

// Order Processing
void GUISystemHandler::processCustomerOrder() {
    std::cout << "Processing customer order" << std::endl;
    std::string customerId = "Customer:" + std::to_string(++customerIdCounter);
    switch (m_window->getProcessOrderState())
    {
    case processOrderState::CUSTOMER_ORDER:
        {
            Customer* order = new Customer(customerId, nurseryHub, greenHouse);
            CommandPtr orderCmd = std::make_shared<SellCommand>(order);
            nurseryHub->assign(orderCmd);
        }
        break;
    case processOrderState::SELF_ORDER:
        {
            std::vector<OrderBuilder*> builders = m_window->getOrderBuilders();
            Customer* order = new Customer(customerId, nurseryHub, builders);
            CommandPtr orderCmd = std::make_shared<SellCommand>(order);
            nurseryHub->assign(orderCmd);
        }
    default:
        break;
    }
}

std::string GUISystemHandler::getGreenhouseSummary() {
    std::stringstream ss;
    ss << "=== GREENHOUSE SUMMARY ===\n\n";
    ss << "Main Greenhouse Section\n";
    ss << "Total Items: " << greenHouse->getTotalItemCount() << "\n";
    ss << "Capacity: 100\n\n";
    ss << "Use 'View Inventory' for detailed item list.\n";
    return ss.str();
}

std::string GUISystemHandler::getInventory() {
    std::stringstream ss;
    ss << "=== INVENTORY ===\n\n";
    ss << "Available Items:\n";
    ss << "- Plants: Rose Plant (R25.00)\n";
    ss << "- Pots: Ceramic Pot (R15.00)\n"; 
    ss << "- Seeds: Sunflower Seeds (R5.00)\n";
    ss << "- Decorations: Glitter Decoration (R8.00)\n\n";
    ss << "Total value: R53.00";
    return ss.str();
}

std::string GUISystemHandler::getStaffInfo() {
    std::stringstream ss;
    ss << "=== STAFF INFORMATION ===\n\n";
    ss << "Registered Staff:\n";
    ss << "- Plant Caretakers: PC1\n";
    ss << "- Sales Managers: SM1\n\n";
    ss << "All staff are available and ready for assignments.";
    return ss.str();
}