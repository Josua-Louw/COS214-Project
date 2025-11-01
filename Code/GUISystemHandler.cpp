#include "GUISystemHandler.h"
#include <iostream>
#include <sstream>

GUISystemHandler::GUISystemHandler() : m_window(nullptr) {
    // Initialize system components
    greenHouse = new Section("Main Greenhouse", 100);
    nurseryHub = new NurseryHub();
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
    std::cout << "Adding plant to greenhouse" << std::endl;
    // Implementation would create a plant and add to greenhouse
    Plant* newPlant = new Plant("Rose Plant", 25.0);
    greenHouse->expand(newPlant);
}

void GUISystemHandler::addPot() {
    std::cout << "Adding pot to greenhouse" << std::endl;
    PotAdapter* newPot = new PotAdapter("Ceramic Pot", 15.0);
    greenHouse->expand(newPot);
}

void GUISystemHandler::addSeedPacket() {
    std::cout << "Adding seed packet to greenhouse" << std::endl;
    SeedPacketAdapter* newSeeds = new SeedPacketAdapter("Sunflower Seeds", 5.0);
    greenHouse->expand(newSeeds);
}

void GUISystemHandler::addDecoration() {
    std::cout << "Adding decoration to greenhouse" << std::endl;
    DecorationAdapter* newDecor = new DecorationAdapter("Glitter Decoration", 8.0);
    greenHouse->expand(newDecor);
}

// Staff Management
void GUISystemHandler::registerStaffMember() {
    // Default implementation
    registerPlantCaretaker();
}

void GUISystemHandler::registerPlantCaretaker() {
    std::cout << "Registering plant caretaker" << std::endl;
    static int caretakerCount = 0;
    std::string id = "PC" + std::to_string(++caretakerCount);
    PlantCaretaker* caretaker = new PlantCaretaker(id, nurseryHub);
    nurseryHub->registerStaff(caretaker);
}

void GUISystemHandler::registerSalesManager() {
    std::cout << "Registering sales manager" << std::endl;
    static int managerCount = 0;
    std::string id = "SM" + std::to_string(++managerCount);
    SalesManager* manager = new SalesManager(id, nurseryHub);
    nurseryHub->registerStaff(manager);
}

void GUISystemHandler::assignCareTask() {
    std::cout << "Assigning care task" << std::endl;
    // Implementation would create a care command and assign via hub
}

void GUISystemHandler::assignSaleTask() {
    std::cout << "Assigning sale task" << std::endl;
    // Implementation would create a sale command and assign via hub
}

// Order Processing
void GUISystemHandler::processCustomerOrder() {
    std::cout << "Processing customer order" << std::endl;
    // Implementation would process the current order
}

void GUISystemHandler::createOrder() {
    std::cout << "Creating new order" << std::endl;
    // Implementation would initialize a new order
}

void GUISystemHandler::addPlantToOrder() {
    std::cout << "Adding plant to order" << std::endl;
    // Implementation would add plant to current order
}

void GUISystemHandler::addPotToOrder() {
    std::cout << "Adding pot to order" << std::endl;
    // Implementation would add pot to current order
}

void GUISystemHandler::addSeedToOrder() {
    std::cout << "Adding seeds to order" << std::endl;
    // Implementation would add seeds to current order
}

void GUISystemHandler::addDecorationToOrder() {
    std::cout << "Adding decoration to order" << std::endl;
    // Implementation would add decoration to current order
}

// Greenhouse Management
void GUISystemHandler::waterAllPlants() {
    std::cout << "Watering all plants" << std::endl;
    // Implementation would water all plants in greenhouse
}

void GUISystemHandler::fertilizeAllPlants() {
    std::cout << "Fertilizing all plants" << std::endl;
    // Implementation would fertilize all plants in greenhouse
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