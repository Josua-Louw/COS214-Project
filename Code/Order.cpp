#include "Order.h"
#include <iostream>
#include <string>
#include <iomanip>

/**
 * @file Order.cpp
 * @brief Implementation of the Order class.
 */

Order::Order() = default;

Order::~Order() {
  for (size_t i = 0; i < items.size(); i++) {
    delete items[i];
  }
  items.clear();
}

Customer* Order::getCustomer() const { 
  return customer; 
}

void Order::setCustomer(Customer* c) { 
  customer = c; 
}

 /**
  * @brief Calculates the total cost of all plants in the order.
  * The method iterates through the collection of plants and sums their individual costs.
  * 
  * @return Total cost of the order as a double.
  */
double Order::getTotalCost() const {
double total = 0.0;
  for (size_t i = 0; i < items.size(); i++) {
    total += items[i]->getPrice();
  }
  return total;
}


/**
 * @brief Adds an item to the order.
 * The method appends the given item to the collection of items in the order.
 * 
 * @param item Pointer to the item to be added to the order.
 */
void Order::addItem(Item* item) {
	if (item){
    //check if item is already in order:
    for (const auto& existingItem : allItems) {
        if (existingItem == item) {
            return;
        }
    }

    if (activePlant && item->getType() != PLANT_TYPE::GREENHOUSE_PLANT)
    {
      OrderPlant* tryDecorate = item->getOrderPlant();
      try
      {
        activePlant->decorate(item->getOrderPlant());
      }
      catch(...)
      {
        items.push_back(tryDecorate);
        activePlant = nullptr;
      }      
    }
    else if (item->getType() == PLANT_TYPE::GREENHOUSE_PLANT)
    {
      activePlant = dynamic_cast<PlantType*>(item->getOrderPlant());
      items.push_back(activePlant);
    }
    else
    {
      items.push_back(item->getOrderPlant());
    }
    allItems.push_back(item);
  }
}

size_t Order::getItemCount() const { 
  return items.size(); 
}

void Order::printOrder() const {
    std::cout << "===== Order Summary =====" << std::endl;
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << std::setw(2) << (i + 1) << ". " << items[i]->getName() << "  -  R" 
                  << std::fixed << std::setprecision(2) << items[i]->getPrice() << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    std::cout << "Total: R" << std::fixed << std::setprecision(2) << getTotalCost() << std::endl;
    std::cout << "==========================" << std::endl;
}

double Order::sellOrder(GreenHouse* gh) {
    double totalRevenue = 0.0;
    for (Item* item : allItems) {
        totalRevenue += gh->sell(item);
    }
    allItems.clear();
    return totalRevenue;
}