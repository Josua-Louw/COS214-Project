#include "TextSystemHandler.h"
#include <limits>

//Helper function to get integer input safely
int getint() {
    int value;
    while (!(std::cin >> value)) { // Attempt to read an integer
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin.clear(); // Clear the error flags
        // Discard invalid input up to the newline character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // Discard any remaining characters on the line after a valid integer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void TextSystemHandler::systemMenue() {
    std::cout << "WELCOME TO THE TEXT-BASED SYSTEM MENU" << std::endl;
    std::cout << "1. Add Plant" << std::endl;
    std::cout << "2. Register Staff Member" << std::endl;
    std::cout << "3. Process Customer Order" << std::endl;
    std::cout << "4. Print GreenHouse Summary" << std::endl;
    std::cout << "5. Quit" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Please select an option (1-5): ";
    int choice = getint();

    switch (choice) {
        case 1:
            addPlant();
            break;
        case 2:
            registerStaffMember();
            break;
        case 3:
            processCustomerOrder();
            break;
        case 4:
            std::cout << "GreenHouse Summary:" << std::endl;
            greenHouse->printSummary();
            systemMenue();
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

// void TextSystemHandler::addSection() {
//     std::cout << "Adding a new section via text interface." << std::endl;
    
//     std::cout << "Enter section name: ";
//     std::string sectionName;
//     std::cin >> sectionName;
//     std::cout << "Enter section capacity: ";
//     size_t capacity;
//     try {
//         std::cin >> capacity;
//     }
//     catch(const std::exception& e) {
//         capacity = 10; // default capacity
//     }
//     greenHouse->expand(new Section(sectionName, capacity));
//     std::cout << "Section '" << sectionName << "' added with capacity " << capacity << "." << std::endl;
//     systemMenue();
// }

void TextSystemHandler::addPlant() {
    std::cout << "Adding a new plant via text interface." << std::endl;
    // std::cout << "Select a section to add an item to: ";
    // std::string sectionName;
    // std::cin >> sectionName;
    // GreenHouse* section = greenHouse->getSubsection(sectionName);
    // if (!section) {
    //     std::cout << "Section not found. Returning to menu." << std::endl;
    //     systemMenue();
    //     return;
    // }
    std::cout << "1. Add Plant" << std::endl;
    std::cout << "2. Add Pot" << std::endl;
    std::cout << "3. Add Seed Packet" << std::endl;
    std::cout << "4. Add Decoration" << std::endl;
    std::cout << "Select item type to add (1-4): ";
    int itemType = getint();
    Item* newItem = nullptr;
    std::cout << "Enter item name: ";
    std::string itemName;
    std::getline(std::cin, itemName);
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
        return;
    }
    greenHouse->expand(newItem);
    //std::cout << "Item '" << itemName << "' added to section '" << sectionName << "'." << std::endl;
    greenHouse->printSummary();
    systemMenue();
}

void TextSystemHandler::registerStaffMember() {
    std::cout << "Registering a new staff member via text interface." << std::endl;
    
    std::cout << "Enter staff member ID: ";
    std::string staffID;
    std::getline(std::cin, staffID);
    
    std::cout << "Select staff role (1. PlantCaretaker, 2. SalesManager): ";
    int roleChoice = getint();
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
    std::getline(std::cin, customerID);
    std::cout << "Enter number of items to order: ";
    int numItems = getint();
    std::vector<std::string> itemNames;
    std::vector<OrderBuilder*> builders;
    for (int i = 0; i < numItems; ++i) {
        std::cout << "1. Plant" << std::endl;
        std::cout << "2. Pot" << std::endl;
        std::cout << "3. Seed Packet" << std::endl;
        std::cout << "4. Decoration" << std::endl;
        std::cout << "Select item type to order (1-4): ";
        int itemType = getint();
        std::cout << "Enter item name: ";
        std::string itemName;
        std::getline(std::cin, itemName);
        itemNames.push_back(itemName);
        switch (itemType)
        {
        case 1:
            builders.push_back(new AddPlant(greenHouse));
            break;
        case 2:
            builders.push_back(new AddPot(greenHouse));
            break;
        case 3:
            builders.push_back(new AddSeed(greenHouse));
            break;
        case 4:
            builders.push_back(new AddDecoration(greenHouse));
            break;
        default:
            break;
        }
    }

    Customer* customer = new Customer(customerID, nurseryHub, builders, itemNames);

    customer->buy();

    std::cout << "Customer order processed for customer ID '" << customerID << "'." << std::endl;
    systemMenue();
}

