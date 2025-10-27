// TestMain for Composite and Iterator
#include <iostream>
#include <string>
#include <vector>
#include "Section.h"
#include "ItemIterator.h"
#include "Plant.h"
#include "PotAdapter.h"
#include "SeedPacketAdapter.h"
#include "DecorationAdapter.h"

int main() {
    std::cout << "=== GREENHOUSE LOCAL TEST ===\n\n";
    Section root("Main Greenhouse", 10);
    Section* treesSection = new Section("Trees", 5);
    Section* potsSection = new Section("Pots", 5);
    root.expand(treesSection);
    root.expand(potsSection);

    std::cout << "-- After explicit subsection expansion --\n";
    root.printSummary();        
    treesSection->printSummary(); 
    potsSection->printSummary();

    std::cout << "\n-- Add items via addItem() (Section routes by type) --\n";
    for (int i = 1; i <= 12; ++i) {     //adding more than 10 to test capacity limit and creation of subsections
        Plant* p = new Plant();       
        root.addItem(p);                
    }

    PotAdapter* pot1 = new PotAdapter(new Pot());
    PotAdapter* pot2 = new PotAdapter(new Pot());
    root.addItem(pot1);
    root.addItem(pot2);

    SeedPacketAdapter* seed1 = new SeedPacketAdapter(new SeedPacket());
    SeedPacketAdapter* seed2 = new SeedPacketAdapter(new SeedPacket());
    root.addItem(seed1);
    root.addItem(seed2);

    DecorationAdapter* deco1 = new DecorationAdapter(new Decoration());
    root.addItem(deco1);

    // Now print summaries (root and some known subsections)
    std::cout << "\n-- Summaries after adds (root and named subsections) --\n";
    root.printSummary();

    // The typed subsections were created by addItem; fetch them by name and inspect:
    Section* plantsSub = dynamic_cast<Section*>(root.getSubsection("Plants"));
    Section* potsSub   = dynamic_cast<Section*>(root.getSubsection("Pots"));
    Section* seedsSub  = dynamic_cast<Section*>(root.getSubsection("Seeds"));
    Section* decorSub  = dynamic_cast<Section*>(root.getSubsection("Decorations"));

    if (plantsSub) {
        std::cout << "\n[Plants subsection summary]\n";
        plantsSub->printSummary();
        // iterate items in the plants subsection and print their names via iterator
        Iterator<Item*>* pit = plantsSub->createIterator();
        for (pit->first(); !pit->isDone(); pit->next()) {
            Item* it = pit->currentItem();
            if (it) std::cout << "  - " << it->getName() << "\n";
        }
        delete pit;
    } else {
        std::cout << "No 'Plants' subsection found.\n";
    }

    if (potsSub) {
        std::cout << "\n[Pots subsection summary]\n";
        potsSub->printSummary();
        Iterator<Item*>* iit = potsSub->createIterator();
        for (iit->first(); !iit->isDone(); iit->next()) {
            Item* it = iit->currentItem();
            if (it) std::cout << "  - " << it->getName() << "\n";
        }
        delete iit;
    }

    if (seedsSub) {
        std::cout << "\n[Seeds subsection summary]\n";
        seedsSub->printSummary();
    }

    if (decorSub) {
        std::cout << "\n[Decorations subsection summary]\n";
        decorSub->printSummary();
    }

    // Demonstrate findItem() (iterator-based) — look for one of the seed adapters (they use getName())
    std::string target = "Rose Seeds"; // adjust to the actual getName() your SeedPacketAdapter returns
    Item* found = root.findItem(target);
    if (found) {
        std::cout << "\nFound item: " << found->getName() << "\n";
        // Now sell the found item via root.sell(found) — Section::sell deletes the item and returns price
        double price = root.sell(found);
        std::cout << "Sold '" << target << "' for R" << price << " (root.sell).\n";
    } else {
        std::cout << "\nItem '" << target << "' not found.\n";
    }

    // Show root summary after sell
    std::cout << "\n-- Root summary after selling --\n";
    root.printSummary();

    cout << "\n=== BUILDER & ORDER TESTS ===" << endl;

    // Create a customer
    shared_ptr<Customer> customer = make_shared<Customer>("Frikkie Malan", "frikkie@example.com");

    // Use the Builder pattern to create an order
    OrderBuilder builder;
    builder.setCustomer(customer)
           .addItem(rose)
           .addItem(aloe)
           .addItem(echeveria);

    shared_ptr<Order> order = builder.build();

    // Print order summary
    order->printSummary();

    // Show order details
    cout << "\nCustomer: " << order->getCustomer()->getName() << endl;
    cout << "Total items in order: " << order->getItemCount() << endl;
    cout << "Total price: R" << order->getTotalPrice() << endl;

    cout << "\n=== ORDER MODIFICATION TEST ===" << endl;
    cout << "Adding a new item (Peace Lily) to the order..." << endl;
    order->addItem(lily);

    order->printSummary();
    cout << "Updated total price: R" << order->getTotalPrice() << endl;

    cout << "\nAll tests completed successfully." << endl;

    std::cout << "\n=== TEST MAIN COMPLETE ===\n";
    return 0;
}
