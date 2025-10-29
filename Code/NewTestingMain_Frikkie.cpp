#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Section.h"
#include "ItemIterator.h"
#include "Plant.h"
#include "PlantImplementor.h"
#include "PotAdapter.h"
#include "SeedPacketAdapter.h"
#include "DecorationAdapter.h"
#include "OrderBuilder.h"
#include "Customer.h"
#include "Order.h"
#include "AddDecoration.h"
#include "AddPlant.h"
#include "AddPot.h"
#include "AddSeed.h"
#include <string>
#include <vector>
#include <functional>

/**
 * @file testingMain.cpp
 * @brief This file contains the main function for running tests using the doctest framework.
 * @details The DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN macro is defined to provide a main function for the test executable.
 * This file should be included in the test build of the project to enable test execution.
 * @note Ensure that the doctest library is properly linked in the test build configuration.
 */

// The main function is provided by the doctest framework when DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN is defined.
// No additional code is needed here.
// This file serves as the entry point for running all tests defined in other test files.

int foo() {
    return 42; // A simple function to demonstrate testing
}

TEST_CASE("Sample Test Case") {
    CHECK(foo() == 42);
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}

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

TEST_CASE("Section pattern and item creation") {
    Section* root = buildGreenHouse();
    CHECK(root != nullptr);
    CHECK(root->getTotalItemCount() == 12);
    Section* plantsSub = dynamic_cast<Section*>(root->getSubsection("Plants"));
    if (plantsSub) {
        CHECK(plantsSub->getItemCount() > 0);
    }
    Item* found = root->findItem("Plant3");
    CHECK(found != nullptr);
    CHECK(found->getName() == "Plant3");
    Item* nfound = root->findItem("Plant15");
    CHECK(nfound == nullptr);
    PotAdapter* pot1 = new PotAdapter(new Pot(10.00, "Blue pot"));
    PotAdapter* pot2 = new PotAdapter(new Pot(15.00, "Silver pot"));
    root->addItem(pot1);
    root->addItem(pot2);
    Section* potSub = dynamic_cast<Section*>(root->getSubsection("Pots"));
    if (potSub) {
        CHECK(potSub->getItemCount() > 0);
    }
    Item* found2 = root->findItem("Blue pot");
    CHECK(found2 != nullptr);
    CHECK(found2->getName() == "Blue pot");
    SeedPacketAdapter* seed1 = new SeedPacketAdapter(new SeedPacket(6.99, "Cucumber seeds"));
    SeedPacketAdapter* seed2 = new SeedPacketAdapter(new SeedPacket(9.99, "Sunflower seeds"));
    root->addItem(seed1);
    root->addItem(seed2);
    Section* seedSub = dynamic_cast<Section*>(root->getSubsection("Seeds"));
    if (seedSub) {
        CHECK(seedSub->getItemCount() > 0);
    }
    Item* found3 = root->findItem("Sunflower seeds");
    CHECK(found3 != nullptr);
    CHECK(found3->getName() == "Sunflower seeds");
    DecorationAdapter* deco1 = new DecorationAdapter(new Decoration(14.99, "Birthday card"));
    DecorationAdapter* deco2 = new DecorationAdapter(new Decoration(9.99, "Red ribbon"));
    root->addItem(deco1);
    root->addItem(deco2);
    Section* decoSub = dynamic_cast<Section*>(root->getSubsection("Decorations"));
    if (decoSub) {
        CHECK(decoSub->getItemCount() > 0);
    }
    Item* found4 = root->findItem("Red ribbon");
    CHECK(found4 != nullptr);
    CHECK(found4->getName() == "Red ribbon");
    std::string target = "Rose seeds"; 
    std::string target2 = "Cucumber seeds";
    found = root->findItem(target);
    found2 = root->findItem(target2);
    CHECK(found == nullptr);
    CHECK(found2 != nullptr);
    CHECK(found2->getName() == "Cucumber seeds");
    CHECK(root->sell(found2) == 6.99);
    REQUIRE_NOTHROW(root->printSummary());
    delete root;
}

TEST_CASE("Builder pattern and order creation") {
    Section* root = buildGreenHouse();
    Order order;
    Customer cust("Frikkie01");
    order.setCustomer(&cust);
    REQUIRE(order.getCustomer() != nullptr);
    CHECK(order.getCustomer()->getId() != "0");
    CHECK(order.getItemCount() == 0);
    CHECK(order.getTotalCost() == 0.00);
    AddPlant plantBuilder(root);
    AddDecoration decoBuilder(root);
    AddPot potBuilder(root);
    AddSeed seedBuilder(root);
    PotAdapter* potX = new PotAdapter(new Pot(10.00, "Blue pot"));
    root->addItem(potX);
    SeedPacketAdapter* seedX = new SeedPacketAdapter(new SeedPacket(6.99, "Cucumber seeds"));
    root->addItem(seedX);
    DecorationAdapter* decoX = new DecorationAdapter(new Decoration(9.99, "Red ribbon"));
    root->addItem(decoX);
    plantBuilder.buildPart(&order, "Golden Rose");
    plantBuilder.buildPart(&order, "Aloe");
    plantBuilder.buildPart(&order, "Plant2");
    decoBuilder.buildPart(&order, "Red ribbon");
    potBuilder.buildPart(&order, "Clay pot");
    potBuilder.buildPart(&order, "Blue pot");
    seedBuilder.buildPart(&order, "Tomato seeds");
    seedBuilder.buildPart(&order, "Cucumber seeds");
    CHECK(order.getItemCount() == 4);
    Plant* peaceLily = new Plant("Peace lily", 49.99);
    CHECK(peaceLily != nullptr);
    order.addItem(peaceLily);
    CHECK(order.getItemCount() == 5);   
    CHECK(order.getTotalCost() > 0);
    REQUIRE_NOTHROW(order.printOrder());
    delete peaceLily;
    delete root;
}

TEST_CASE("Iterator traversal") {
    Section* root = buildGreenHouse();
    Iterator<Item*>* rootIt = root->createIterator();
    int localCount = 0;
    for (rootIt->first(); !rootIt->isDone(); rootIt->next()) {
        Item* current = rootIt->currentItem();
        CHECK(current != nullptr);
        ++localCount;
    }
    CHECK(localCount == 0);
    delete rootIt;
    std::function<int(GreenHouse*)> countAll = [&](GreenHouse* gh) -> int {
        if (!gh) return 0;
        Section* section = dynamic_cast<Section*>(gh);
        if (!section) return 0;
        int subtotal = 0;
        Iterator<Item*>* it = section->createIterator();
        for (it->first(); !it->isDone(); it->next()) {
            Item* current = it->currentItem();
            if (current) ++subtotal;
        }
        delete it;
        const char* subsectionNames[] = {
            "Plants", "Pots", "Seeds", "Decorations", "Trees",
            "Plants_Subsection_2", "Plants_Subsection_3"
        };
        for (auto name : subsectionNames) {
            GreenHouse* sub = section->getSubsection(name);
            if (sub) subtotal += countAll(sub);
        }
        return subtotal;
    };
    int totalCount = countAll(root);
    CHECK(totalCount == root->getTotalItemCount());
    delete root;
}
