#include "GUISystemHandler.h"
#include <iostream>

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
    for (auto strategy : careStrategies) {
        delete strategy;
    }
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
        int strategyIndex = rand() % careStrategies.size();
        std::string plantName = plantNames[index].first;
        double plantPrice = plantNames[index].second;
        Plant* newPlant = new Plant(plantName, plantPrice, nurseryHub, careStrategies[strategyIndex]);
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
    double initialAmountInGreenHouse = 0.0;
    Iterator<Item*>* it = greenHouse->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        Item* item = it->currentItem();
        if (item) {
            initialAmountInGreenHouse += item->getPrice();
        }
    }
    switch (m_window->getProcessOrderState())
    {
    case processOrderState::CUSTOMER_ORDER:
        {
            Customer* order = new Customer(customerId, nurseryHub, greenHouse);
            CommandPtr orderCmd = std::make_shared<SellCommand>(order);
            nurseryHub->assign(orderCmd);
            delete order;
        }
        break;
    case processOrderState::SELF_ORDER:
        {
            std::vector<OrderBuilder*> builders = m_window->getOrderBuilders();
            Customer* order = new Customer(customerId, nurseryHub, builders);
            CommandPtr orderCmd = std::make_shared<SellCommand>(order);
            nurseryHub->assign(orderCmd);
            delete order;
        }
        break;
    default:
        std::cout << "invalid order state" << std::endl;
        break;
    }
    double finalAmountInGreenHouse = 0.0;
    delete it;
    it = greenHouse->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        Item* item = it->currentItem();
        if (item) {
            finalAmountInGreenHouse += item->getPrice();
        }
    }
    double moneyEarned = initialAmountInGreenHouse - finalAmountInGreenHouse;
    double currentMoneyInTheBank = m_window->getMoneyInTheBank();
    m_window->setMoneyInTheBank(currentMoneyInTheBank + moneyEarned);
    delete it;
}

std::string GUISystemHandler::getGreenhouseSummary() {
    std::stringstream ss;
    ss << "=== GREENHOUSE SUMMARY ===\n\n";
    ss << greenHouse->getName() << " Section\n";
    ss << "Total Items: " << greenHouse->getTotalItemCount() << "\n";
    ss << "Capacity: 100\n\n";
    ss << "Use 'View Inventory' for detailed item list.\n";
    return ss.str();
}

std::string GUISystemHandler::getInventory() {
    std::stringstream ss;
    ss << "=== INVENTORY ===\n\n";
    ss << "Available Items:\n";
    double totalValue = 0.0;
    Iterator<Item*>* it = greenHouse->createIterator();
    for (it->first(); !it->isDone(); it->next()) {
        Item* item = it->currentItem();
        if (item) {
            ss << "- " << item->getName() << " | Price: R" << item->getPrice() << "\n";
            totalValue += item->getPrice();
        }
    }
    delete it;

    ss << "Total value: R" << totalValue << "\n";
    return ss.str();
}

std::string GUISystemHandler::getStaffInfo() {
    return nurseryHub->getStaffInfo();
}