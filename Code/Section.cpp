#include "Section.h"

/**
 * @file Section.cpp
 * @brief Implementation of the Section class.
 * 
 * @todo Implement the methods expand, getSubsection, sell, CreateIterator, findItem, addItem and printSection methods.
*/

/**
 * @brief Creates a greenhouse section by adding a subsection (leaf) of the GreenHouse class.
 * 
 * @param sectionName Name of the section to be created (composite).
 * @param cap Capacity of the items that the section may hold. Default = 10.
*/ 
Section::Section(const std::string& sectionName, size_t cap)
       : name(sectionName), capacity(cap) {}

/**
 * @brief Destructor for a section object.
 */
Section::~Section() {
    for (int i = 0; i < (int)section.size(); i++) {
        delete section[i];
    }
    section.clear();
	for (int j = 0; j < (int)items.size(); j++) {
        delete items[j];
    }
    items.clear();
}

/**
 * @brief Expands the greenhouse by adding a subsection (leaf) of the GreenHouse class.
 * 
 * @param greenHouse Pointer to the current subsection to be added (composite).
*/ 
void Section::expand(GreenHouse* greenHouse) {
	if (greenHouse != nullptr){
		section.push_back(greenHouse);
	}
}

/**
 * @brief Searches the greenhouse for a specific subsection (leaf) that belongs to the GreenHouse class.
 * 
 * @param sectionName String description of the section to be searched for.
 * 
 * @return Pointer to the greenhouse section that was searched for, or nullptr if not found.
*/ 
GreenHouse* Section::getSubsection(const std::string& sectionName) {
	for (int i = 0; i < (int)section.size(); i++) {
        if (section[i]->getName() == sectionName) {
            return section[i];
        }
    }
    return nullptr;
}

/**
 * @brief Sell an item represented by the given GreenHouse node.
 * 
 * @param Item GreenHouse node (an Item* that is to be sold).
 * 
 * @return Total price of the item (double).
*/ 
double Section::sell(Item* item) {
    if (item == nullptr) {
        return 0.0;
    }
    for (int i = 0; i < (int)items.size(); i++) {
        if (items[i] == item) {
            double price = items[i]->getPrice();
            delete items[i];
            items.erase(items.begin() + i);
            return price;
        }
    }
    for (int i = 0; i < (int)section.size(); i++) {
        Section* sub = dynamic_cast<Section*>(section[i]);
        if (sub != nullptr) {
            double result = sub->sell(item);
            if (result > 0.0) {
                return result;
            }
        }
    }
    return 0.0;
}

/**
 * @brief Create a concrete iterator for traversing contained items.
 * 
 * @return Pointer to the dynamically allocated Iterator* (caller responsible for delete).
*/ 
Iterator<Item*>* Section::createIterator() {
    return new ItemIterator(items);
}

/**
 * @brief Find a plant by name (string) inside this node/subsection of the greenhouse.
 * 
 * @param itemName Plant name to be searched for.
 * 
 * @return Pointer to the item (Item*), otherwise nullptr if not found.
*/ 
Item* Section::findItem(const std::string& itemName) {
    Iterator<Item*>* localIterator = createIterator();
    for (localIterator->first(); !localIterator->isDone(); localIterator->next()) {
        Item* item = localIterator->currentItem();
        if (item != nullptr && item->getName() == itemName) {
            delete localIterator;
            return item;
        }
    }
    delete localIterator;
    for (int i = 0; i < (int)section.size(); i++) {
        Iterator<Item*>* subIterator = section[i]->createIterator();
        for (subIterator->first(); !subIterator->isDone(); subIterator->next()) {
            Item* item = subIterator->currentItem();
            if (item != nullptr && item->getName() == itemName) {
                delete subIterator;
                return item;
            }
        }
        delete subIterator;
    }
    return nullptr;
}

/**
 * @brief Adds an Item (Plant, Pot, Decoration, etc.) to the section.
 * 
 * @param item Pointer to the Item to be added.
 * 
 * @details Groups items logically by type using runtime type identification (RTTI).
 * If the section reaches its capacity, a new subsection is created.
 */
void Section::addItem(Item* item) {
	if (!item) return;
    std::string sectionType;
    if (dynamic_cast<Plant*>(item)) {
        sectionType = "Plants";
    }
    else if (dynamic_cast<PotAdapter*>(item)) {
        sectionType = "Pots";
    }
    else if (dynamic_cast<DecorationAdapter*>(item)) {
        sectionType = "Decorations";
    }
    else if (dynamic_cast<SeedPacketAdapter*>(item)) {
        sectionType = "Seeds";
    }
    else {
        sectionType = "Miscellaneous";
    }
    Section* targetSection = dynamic_cast<Section*>(getSubsection(sectionType));
    if (!targetSection) {
        targetSection = new Section(sectionType, capacity);
        expand(targetSection);
    }
    if (targetSection->items.size() >= capacity) {
        std::string newSubName = sectionType + "_Subsection_" + std::to_string(section.size() + 1);
        Section* newSub = new Section(newSubName, capacity);
        expand(newSub);
        targetSection = newSub;
    } 
    targetSection->items.push_back(item);
}

/**
 * @brief Returns the name of this section (getter).
 * 
 * @return String name of this section.
 */
std::string Section::getName() const {
    return name;
}

size_t Section::getItemCount() const {
    return items.size();
}

size_t Section::getTotalItemCount() const {			//HELPER
    size_t total = items.size();
    for (size_t i = 0; i < section.size(); i++) {
        total += section[i]->getTotalItemCount();
    }
    return total;
}


/**
 * @brief Prints a summary of this section and its subsections.
 */
void Section::printSummary() const {
    printSummaryHelper(0);
}

void Section::printSummaryHelper(int indentLevel) const {
    std::string indent(indentLevel * 2, ' ');
    std::cout << indent << "Section: " << name << std::endl;
    std::cout << indent << "  Items (local): " << items.size() << " | Total (with subsections): " << getTotalItemCount() << std::endl;
    if (!items.empty()) {
        for (size_t i = 0; i < items.size(); ++i) {
            std::string itemName = items[i]->getName();
            if (itemName.empty())
                itemName = "(Unnamed)";
            std::cout << indent << "  - " << itemName << std::endl;
        }
    }
    if (!section.empty()) {
        std::cout << indent << "  Subsections:" << std::endl;
        for (size_t i = 0; i < section.size(); ++i) {
            section[i]->printSummaryHelper(indentLevel + 1);
        }
    }
}