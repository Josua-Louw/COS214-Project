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
    std::cout << "Select a section to add the plant to: ";
    std::string sectionName;
    std::cin >> sectionName;
    GreenHouse* section = greenHouse->getSubsection(sectionName);
    if (!section) {
        std::cout << "Section not found. Returning to menu." << std::endl;
        systemMenue();
        return;
    }
    std::cout << "Enter plant name: ";
    std::string plantName;
    std::cin >> plantName;
    std::cout << "Enter plant price: ";
    double plantPrice;
    try {
        std::cin >> plantPrice;
    }  catch(const std::exception& e) {
        plantPrice = 0.0; // default price
    }
    Plant* newPlant = new Plant(new GreenHousePlant());
    section->expand(newPlant);
    std::cout << "Plant '" << plantName << "' added to section '" << sectionName << "'." << std::endl;
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
    Person* newStaff = nullptr;
    if (roleChoice == 1) {
        newStaff = new PlantCaretaker(staffID, nurseryHub);
    } else if (roleChoice == 2) {
        newStaff = new SalesManager(staffID, nurseryHub);
    } else {
        std::cout << "Invalid role choice. Returning to menu." << std::endl;
        systemMenue();
        return;
    }
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