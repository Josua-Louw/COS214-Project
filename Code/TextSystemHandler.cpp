#include "TextSystemHandler.h"

void TextSystemHandler::systemMenue() {
    std::cout << "WELCOME TO THE TEXT-BASED SYSTEM MENU" << std::endl;
    std::cout << "1. Add Section" << std::endl;
    std::cout << "2. Add Plant" << std::endl;
    std::cout << "3. Register Staff Member" << std::endl;
    std::cout << "4. Process Customer Order" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Please select an option (1-5): ";
    int choice = 0;
    try
    {
        std::cin >> choice;
    }
    catch(const std::exception& e) {}

    switch (choice) {
        case 1:
            addSection();
            break;
        case 2:
            addPlant();
            break;
        case 3:
            registerStaffMember();
            break;
        case 4:
            processCustomerOrder();
            break;
        case 5:
            std::cout << "Exiting the system. Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            systemMenue();
            break;
    }
}

void TextSystemHandler::addSection() {
    std::cout << "Adding a new section via text interface." << std::endl;
    
    std::cout << "Enter section name: ";
    std::string sectionName;
    std::cin >> sectionName;
    std::cout << "Enter section capacity: ";
    size_t capacity;
    try {
        std::cin >> capacity;
    }
    catch(const std::exception& e) {
        capacity = 10; // default capacity
    }
    greenHouse->expand(new Section(sectionName, capacity));
    std::cout << "Section '" << sectionName << "' added with capacity " << capacity << "." << std::endl;
    systemMenue();
}

void TextSystemHandler::addPlant() {
    std::cout << "Adding a new plant via text interface." << std::endl;
    std::cout << "Select a section to add an item to: ";
    std::string sectionName;
    std::cin >> sectionName;
    GreenHouse* section = greenHouse->getSubsection(sectionName);
    if (!section) {
        std::cout << "Section not found. Returning to menu." << std::endl;
        systemMenue();
        return;
    }
    std::cout << "1. Add Plant" << std::endl;
    std::cout << "2. Add Pot" << std::endl;
    std::cout << "3. Add Seed Packet" << std::endl;
    std::cout << "4. Add Decoration" << std::endl;
    std::cout << "Select item type to add (1-4): ";
    int itemType;
    try {
        std::cin >> itemType;
    } catch(const std::exception& e) {
        itemType = 1; // default to Plant
    }
    Item* newItem = nullptr;
    std::cout << "Enter item name: ";
    std::string itemName;
    std::cin >> itemName;
    std::cout << "Enter item price: ";
    double itemPrice;
    try {
        std::cin >> itemPrice;
    } catch(const std::exception& e) {
        itemPrice = 0.0; // default price
    }
    switch (itemType)
    {
    case 1:
        newItem = new Plant(itemName, itemPrice);
        break;
    case 2:
        newItem = new PotAdapter(itemName, itemPrice);
        break;
    case 3:
        newItem = new SeedPacketAdapter(itemName, itemPrice);
        break;
    case 4:
        newItem = new DecorationAdapter(itemName, itemPrice);
        break;
    default:
        break;
    }
    section->expand(newItem);
    std::cout << "Item '" << itemName << "' added to section '" << sectionName << "'." << std::endl;
    systemMenue();
}

void TextSystemHandler::registerStaffMember() {
    std::cout << "Registering a new staff member via text interface." << std::endl;
    
    std::cout << "Enter staff member ID: ";
    std::string staffID;
    std::cin >> staffID;
    
    std::cout << "Select staff role (1. PlantCaretaker, 2. SalesManager): ";
    int roleChoice;
    try {
        std::cin >> roleChoice;
    } catch(const std::exception& e) {
        roleChoice = 1; // default role
    }
    Staff* newStaff = nullptr;
    if (roleChoice == 1) {
        newStaff = new PlantCaretaker(staffID, nurseryHub);
        nurseryHub->registerStaff(newStaff);
    } else if (roleChoice == 2) {
        newStaff = new SalesManager(staffID, nurseryHub);
        nurseryHub->registerStaff(newStaff);
    } else {
        std::cout << "Invalid role choice. Returning to menu." << std::endl;
    }
    systemMenue();
}

void TextSystemHandler::processCustomerOrder() {
    std::cout << "Processing a customer order via text interface." << std::endl;
    
    std::cout << "Enter customer ID: ";
    std::string customerID;
    std::cin >> customerID;
    Customer* customer = new Customer(customerID, nurseryHub);

    customer->buy();

    std::cout << "Customer order processed for customer ID '" << customerID << "'." << std::endl;
    systemMenue();
}