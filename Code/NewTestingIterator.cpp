#include <iostream>
#include "Section.h"
#include "Item.h"
#include "ItemIterator.h"

static Section* buildGreenHouse() {      //HELPER
   Section* root = new Section("Main Greenhouse", 10);
    for (int i = 1; i <= 10; ++i) {
        root->addItem(new Plant("Plant" + std::to_string(i), 10.0 + i));
    }
    root->addItem(new Plant("Extra1", 15.0));
    root->addItem(new Plant("Extra2", 16.0));
    Section* treesSection = new Section("Trees", 5);
    root->expand(treesSection);
    return root;
}
    

int main() {
    Section* root = buildGreenHouse();
    root->getTotalItemCount();

    Section* subSection2 = new Section("Trees_1");
    subSection2->addItem(new Plant("Weeping willow", 50.00));
    subSection2->addItem(new Plant("Rooi karee", 45.00));

    root->expand(subSection2);

    Iterator<Item*>* iterator = root->createIterator();

    std::cout << "---- Testing recursive item traversal ----" << std::endl;
    int count = 0;

    for (iterator->first(); !iterator->isDone(); iterator->next()) {
        Item* current = iterator->currentItem();
        if (current != nullptr) {
            std::cout << "Found item: " << current->getName() << std::endl;
            count++;
        }
    }

    std::cout << "\nTotal items found (including subsections): " << count << std::endl;

    delete iterator;
    delete root;  
    return 0;
}
