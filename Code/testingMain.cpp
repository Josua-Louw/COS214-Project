#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN //Do not define this anywhere else
#include "doctest.h"
#include "FertilizePlant.h"
#include "WaterPlant.h"
#include "SellCommand.h"
#include "PlantCaretaker.h"
#include "SalesManager.h"
#include "NurseryHub.h"
#include "GreenHousePlant.h"
#include "Plant.h"
#include "Order.h"
#include "GreenHouse.h"
#include <string>

#include "GreenHousePlant.h"
#include "RegularCareStrategy.h"
#include "FertilizerBoostStrategy.h"
#include "WaterLimitingStrategy.h"


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

/**
 * @brief Minimal mock for NurseryHub to test notifications.
 */
// class MockNurseryHub : public NurseryHub {
// public:
//     bool notified = false;
//     std::string lastEvent;
//     std::string lastData;

//     void notify(void* sender, std::string event, std::string data) override {
//         notified = true;
//         lastEvent = event;
//         lastData = data;
//     }
//     void assign(Command* cmd) override {}
//     void registerPlant(Plant* p) override {}
//     void registerStaff(Staff* s) override {}
// };

// /**
//  * @brief Minimal mock for GreenHousePlant and Plant to test commands.
//  * @brief Minimal mock for GreenHousePlant to test FertilizePlant, WaterPlant, and SellCommand.
//  */
// class MockGreenHousePlant : public GreenHousePlant, public Plant {
// public:
//     bool fed = false;
//     bool watered = false;
//     double price = 10.0;
//     std::string name = "Rose";

//     // GreenHousePlant methods
//     void feed() { fed = true; }
//     void water() { watered = true; }
//     double getPrice() const { return price; }
//     PLANT_TYPE getType() const { return PLANT_TYPE::GREENHOUSE_PLANT; }
//     PlantImplementor* clone() { return new MockGreenHousePlant(*this); }
//     std::string getName() const { return name; } // Satisfies Item::getName

//     // Plant methods
//     void convertToOrderType() {}
//     std::string getImplementorType() { return "MockGreenHousePlant"; }

//     // GreenHouse methods (via Item)
//     double sell(GreenHouse* item) {
//         if (dynamic_cast<MockGreenHousePlant*>(item) == this) {
//             return price;
//         }
//         return 0.0;
//     }
//     void expand(GreenHouse*) {}
//     GreenHouse* getSubsection(std::string) { return nullptr; }
//     Iterator* CreateIterator() { return nullptr; }
//     Plant* findItem(std::string itemName) {
//         return (itemName == name) ? this : nullptr;
//     }
// };

// /**
//  * @brief Minimal mock for Order to test SellCommand.
//  */
// class MockOrder : public Order {
// public:
//     bool plantAdded = false;
//     Plant* addedPlant = nullptr;

//     void addPlant(Plant* p) {
//         plantAdded = true;
//         addedPlant = p;
//     }
// };

// TEST_CASE("Chain of Responsibility Tests for PlantCaretaker and SalesManager") {
//     MockNurseryHub* hub = new MockNurseryHub();
//     MockGreenHousePlant* plant = new MockGreenHousePlant();
//     MockOrder* order = new MockOrder();

//     SUBCASE("PlantCaretaker handles WaterPlant command") {
//         PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
//         WaterPlant* cmd = new WaterPlant(plant);

//         bool handled = caretaker->handleRequest(cmd);
//         CHECK(handled == true);
//         CHECK(plant->watered == true);
//         CHECK(caretaker->getTaskList().size() == 1);
//         CHECK(caretaker->getNextStaff() == nullptr);
//         CHECK(hub->notified == true);
//         CHECK(hub->lastEvent == "CARE_COMPLETED");
//         CHECK(hub->lastData == "Plant cared for");

//         delete cmd;
//         delete caretaker;
//     }

//     SUBCASE("PlantCaretaker handles FertilizePlant command") {
//         PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
//         FertilizePlant* cmd = new FertilizePlant(plant);

//         bool handled = caretaker->handleRequest(cmd);
//         CHECK(handled == true);
//         CHECK(plant->fed == true);
//         CHECK(caretaker->getTaskList().size() == 1);
//         CHECK(caretaker->getNextStaff() == nullptr);
//         CHECK(hub->notified == true);
//         CHECK(hub->lastEvent == "CARE_COMPLETED");
//         CHECK(hub->lastData == "Plant cared for");

//         delete cmd;
//         delete caretaker;
//     }

//     SUBCASE("PlantCaretaker delegates SellCommand to SalesManager") {
//         PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
//         SalesManager* manager = new SalesManager("SM1", hub);
//         caretaker->setNextStaff(manager);
//         SellCommand* cmd = new SellCommand(plant, order);

//         bool handled = caretaker->handleRequest(cmd);
//         CHECK(handled == true);
//         CHECK(caretaker->getTaskList().size() == 0);
//         CHECK(caretaker->getNextStaff() == manager);
//         CHECK(manager->getTaskList().size() == 1);
//         CHECK(manager->getNextStaff() == nullptr);
//         CHECK(order->plantAdded == true);
//         CHECK(order->addedPlant == static_cast<Plant*>(plant));
//         CHECK(hub->notified == true);
//         CHECK(hub->lastEvent == "SALE_COMPLETED");
//         CHECK(hub->lastData == "Order processed");

//         delete cmd;
//         delete manager;
//         delete caretaker;
//     }

//     SUBCASE("SalesManager handles SellCommand") {
//         SalesManager* manager = new SalesManager("SM1", hub);
//         SellCommand* cmd = new SellCommand(plant, order);

//         bool handled = manager->handleRequest(cmd);
//         CHECK(handled == true);
//         CHECK(order->plantAdded == true);
//         CHECK(order->addedPlant == static_cast<Plant*>(plant));
//         CHECK(manager->getTaskList().size() == 1);
//         CHECK(manager->getNextStaff() == nullptr);
//         CHECK(hub->notified == true);
//         CHECK(hub->lastEvent == "SALE_COMPLETED");
//         CHECK(hub->lastData == "Order processed");

//         delete cmd;
//         delete manager;
//     }

//     SUBCASE("SalesManager delegates WaterPlant to PlantCaretaker") {
//         SalesManager* manager = new SalesManager("SM1", hub);
//         PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
//         manager->setNextStaff(caretaker);
//         WaterPlant* cmd = new WaterPlant(plant);

//         bool handled = manager->handleRequest(cmd);
//         CHECK(handled == true);
//         CHECK(manager->getTaskList().size() == 0);
//         CHECK(manager->getNextStaff() == caretaker);
//         CHECK(caretaker->getTaskList().size() == 1);
//         CHECK(caretaker->getNextStaff() == nullptr);
//         CHECK(plant->watered == true);
//         CHECK(hub->notified == true);
//         CHECK(hub->lastEvent == "CARE_COMPLETED");
//         CHECK(hub->lastData == "Plant cared for");

//         delete cmd;
//         delete caretaker;
//         delete manager;
//     }

//     SUBCASE("No staff handles unmatched command") {
//         PlantCaretaker* caretaker = new PlantCaretaker("PC1", hub);
//         SalesManager* manager = new SalesManager("SM1", hub);
//         caretaker->setNextStaff(manager);
//         class DummyCommand : public Command {
//         public:
//             void execute() override {}
//         };
//         DummyCommand* cmd = new DummyCommand();

//         bool handled = caretaker->handleRequest(cmd);
//         CHECK(handled == false);
//         CHECK(caretaker->getTaskList().size() == 0);
//         CHECK(manager->getTaskList().size() == 0);
//         CHECK(caretaker->getNextStaff() == manager);
//         CHECK(manager->getNextStaff() == nullptr);
//         CHECK(hub->notified == false);

//         delete cmd;
//         delete manager;
//         delete caretaker;
//     }

//     delete plant;
//     delete order;
//     delete hub;
// }

// TEST_CASE("FertilizePlant Command Tests") {
//     SUBCASE("Execute calls feed on valid GreenHousePlant") {
//         MockGreenHousePlant* plant = new MockGreenHousePlant();
//         FertilizePlant cmd(plant);
//         cmd.execute();

//         CHECK(plant->fed == true);

//         delete plant;
//     }

//     SUBCASE("Execute with null plant does nothing") {
//         FertilizePlant cmd(nullptr);
//         CHECK_NOTHROW(cmd.execute());
//     }
// }

// TEST_CASE("WaterPlant Command Tests") {
//     SUBCASE("Execute calls water on valid GreenHousePlant") {
//         MockGreenHousePlant* plant = new MockGreenHousePlant();
//         WaterPlant cmd(plant);
//         cmd.execute();

//         CHECK(plant->watered == true);

//         delete plant;
//     }

//     SUBCASE("Execute with null plant does nothing") {
//         WaterPlant cmd(nullptr);
//         CHECK_NOTHROW(cmd.execute());
//     }
// }

// TEST_CASE("SellCommand Command Tests") {
//     SUBCASE("Execute calls addPlant and sell on valid Plant and Order") {
//         MockGreenHousePlant* plant = new MockGreenHousePlant();
//         MockOrder* order = new MockOrder();
//         SellCommand cmd(plant, order); // MockGreenHousePlant* is a Plant*
//         cmd.execute();

//         CHECK(order->plantAdded == true);
//         CHECK(order->addedPlant == static_cast<Plant*>(plant));
//         CHECK(plant->sell(static_cast<GreenHouse*>(plant)) == 10.0);

//         delete plant;
//         delete order;
//     }

//     SUBCASE("Execute with null plant or order does nothing") {
//         MockGreenHousePlant* plant = new MockGreenHousePlant();
//         MockOrder* order = new MockOrder();
//         SellCommand cmd1(nullptr, order);
//         SellCommand cmd2(plant, nullptr);
//         SellCommand cmd3(nullptr, nullptr);

//         CHECK_NOTHROW(cmd1.execute());
//         CHECK_NOTHROW(cmd2.execute());
//         CHECK_NOTHROW(cmd3.execute());
//         CHECK(order->plantAdded == false);

//         delete plant;
//         delete order;
//     }
// }



int foo() {
    return 42; // A simple function to demonstrate testing
}

TEST_CASE("Sample Test Case") {
    CHECK(foo() == 42);
    CHECK(1 + 1 == 2);
    CHECK(2 * 2 == 4);
}

// ---- Strategy tests ----

TEST_CASE("RegularCare increases hydration & nutrition") {
    GreenHousePlant p;
    RegularCareStrategy s;
    p.setStrategy(&s);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 3);
    CHECK(p.getNutrition() == n0 + 2);
}

TEST_CASE("FertilizerBoost focuses on nutrition") {
    GreenHousePlant p;
    FertilizerBoostStrategy s;
    p.setStrategy(&s);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 2);
    CHECK(p.getNutrition() == n0 + 5);
}

TEST_CASE("WaterLimiting reduces watering pressure") {
    GreenHousePlant p;
    WaterLimitingStrategy s;
    p.setStrategy(&s);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 1);
    CHECK(p.getNutrition() == n0 + 2);
}

TEST_CASE("Switching strategies changes behavior at runtime") {
    GreenHousePlant p;
    RegularCareStrategy reg;
    FertilizerBoostStrategy fert;

    p.setStrategy(&reg);
    int h0 = p.getHydration(), n0 = p.getNutrition();
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 3);
    CHECK(p.getNutrition() == n0 + 2);

    p.setStrategy(&fert);
    p.applyCurrentCare();
    CHECK(p.getHydration() == h0 + 3 + 2); // +2 more from fert
    CHECK(p.getNutrition() == n0 + 2 + 5); // +5 more from fert
}
//TEST for seed packet functionality
#include "SeedPacket.h"

TEST_CASE("Seed Packet Test Case") {
    SUBCASE("Default Constructor") {
        SeedPacket sp;
        CHECK(sp.getPrice() == 0.0);
        CHECK(sp.getName() == "");
    }
    SUBCASE("Parameterized Constructor") {
        SeedPacket sp2(10.0, "Rose Seeds");
        CHECK(sp2.getPrice() == 10.0);
        CHECK(sp2.getName() == "Rose Seeds");
        CHECK(sp2.getType() == PLANT_TYPE::SEED_PACKET);
    }
    SUBCASE("Copy Constructor") {
        SeedPacket sp3(15.0, "Tulip Seeds");
        SeedPacket sp4(sp3);
        CHECK(sp4.getPrice() == 15.0);
        CHECK(sp4.getName() == "Tulip Seeds");
        CHECK(sp4.getType() == PLANT_TYPE::SEED_PACKET);
    }
    SUBCASE("Clone Method") {
        SeedPacket sp5(20.0, "Daisy Seeds");
        PlantImplementor* spClone = sp5.clone();
        SeedPacket* spCloneCasted = dynamic_cast<SeedPacket*>(spClone);
        REQUIRE(spCloneCasted != nullptr);
        CHECK(spCloneCasted->getPrice() == 20.0);
        CHECK(spCloneCasted->getName() == "Daisy Seeds");
        CHECK(spCloneCasted->getType() == PLANT_TYPE::SEED_PACKET);
        delete spClone; // Clean up cloned object
    }
    SUBCASE("Decorate Method") {
        SeedPacket sp6(25.0, "Sunflower Seeds");
        // Since decorate does nothing for SeedPacket, just ensure it doesn't throw
        CHECK_NOTHROW(sp6.decorate(&sp6));
        CHECK(sp6.getPrice() == 25.0); // Price should remain unchanged
    }
}

//TEST for Decorator functionality
#include "Decoration.h"

TEST_CASE("Decoration Test Case") {
    SUBCASE("Default Constructor") {
        Decoration dec;
        CHECK(dec.getPrice() == 0.0);
        CHECK(dec.getName() == "");
    }
    SUBCASE("Parameterized Constructor") {
        Decoration dec2(5.0, "Glitter");
        CHECK(dec2.getPrice() == 5.0);
        CHECK(dec2.getName() == "Glitter");
        CHECK(dec2.getType() == PLANT_TYPE::DECORATION);
    }
    SUBCASE("Copy Constructor") {
        Decoration dec3(7.5, "Ribbons");
        Decoration dec4(dec3);
        CHECK(dec4.getPrice() == 7.5);
        CHECK(dec4.getName() == "Ribbons");
        CHECK(dec4.getType() == PLANT_TYPE::DECORATION);
    }
    SUBCASE("Clone Method") {
        Decoration dec5(12.0, "Beads");
        PlantImplementor* decClone = dec5.clone();
        Decoration* decCloneCasted = dynamic_cast<Decoration*>(decClone);
        REQUIRE(decCloneCasted != nullptr);
        CHECK(decCloneCasted->getPrice() == 12.0);
        CHECK(decCloneCasted->getName() == "Beads");
        CHECK(decCloneCasted->getType() == PLANT_TYPE::DECORATION);
        delete decClone; // Clean up cloned object
    }
    SUBCASE("Decoration on SeedPacket") {
        SeedPacket* sp = new SeedPacket(10.0, "Sunflower Seeds");
        Decoration dec(3.0, "Sparkles");
        dec.decorate(sp);
        CHECK(dec.getPrice() == 13.0); // 10 + 3
        CHECK(sp->getPrice() == 10.0); // Original seed packet price remains unchanged
        CHECK(sp->getName() == "Sunflower Seeds");
        CHECK(sp->getType() == PLANT_TYPE::SEED_PACKET);
        CHECK(dec.getType() == PLANT_TYPE::DECORATION);
        CHECK(dec.getName() == "Sparkles | Sunflower Seeds");
        SUBCASE("Double Decoration with seeds Error") {
            SeedPacket* sp2 = new SeedPacket(2.0, "Glitter");
            CHECK_THROWS_AS(dec.decorate(sp2), const char*);
            delete sp2; // Clean up seed packet
        }
        SUBCASE("Decoration Chain") {
            Decoration* dec2 = new Decoration(2.0, "Ribbons");
            dec.decorate(dec2);
            CHECK(dec.getPrice() == 15.0); // 10 + 3 + 2
            CHECK(dec2->getName() == "Ribbons | Sunflower Seeds");
            CHECK(dec2->getType() == PLANT_TYPE::DECORATION);
        }
        SUBCASE("Longer decoration Chain") {
            Decoration newDec(3.0, "Flowers");
            Decoration* dec3 = new Decoration(1.0, "Beads");
            Decoration* dec4 = new Decoration(2.0, "Lights");
            newDec.decorate(dec3);
            newDec.decorate(dec4);
            CHECK(newDec.getPrice() == 6.0); // 3 + 1 + 2
        }
        SUBCASE("Null Decoration") {
            Decoration decNull(4.0, "Feathers");
            decNull.decorate(nullptr); // Should handle gracefully
            CHECK(decNull.getPrice() == 4.0); // Price remains unchanged
        }
    }    
}

//TEST for Pot functionality
#include "Pot.h"

TEST_CASE("Pot Test Case") {
    SUBCASE("Default Constructor") {
        Pot pot;
        CHECK(pot.getPrice() == 0.0);
        CHECK(pot.getName() == "");
    }
    SUBCASE("Parameterized Constructor") {
        Pot pot2(8.0, "Ceramic Pot");
        CHECK(pot2.getPrice() == 8.0);
        CHECK(pot2.getName() == "Ceramic Pot");
        CHECK(pot2.getType() == PLANT_TYPE::POT);
    }
    SUBCASE("Copy Constructor") {
        Pot pot3(12.0, "Plastic Pot");
        Pot pot4(pot3);
        CHECK(pot4.getPrice() == 12.0);
        CHECK(pot4.getName() == "Plastic Pot");
        CHECK(pot4.getType() == PLANT_TYPE::POT);
    }
    SUBCASE("Clone Method") {
        Pot pot5(15.0, "Clay Pot");
        PlantImplementor* potClone = pot5.clone();
        Pot* potCloneCasted = dynamic_cast<Pot*>(potClone);
        REQUIRE(potCloneCasted != nullptr);
        CHECK(potCloneCasted->getPrice() == 15.0);
        CHECK(potCloneCasted->getName() == "Clay Pot");
        CHECK(potCloneCasted->getType() == PLANT_TYPE::POT);
        delete potClone; // Clean up cloned object
    }
}

//TEST for PlantType functionality
#include "PlantType.h"

TEST_CASE("PlantType Test Case") {
    SUBCASE("Default Constructor") {
        PlantType pt;
        CHECK(pt.getPrice() == 0.0);
        CHECK(pt.getName() == "");
    }
    SUBCASE("Parameterized Constructor") {
        PlantType pt2(20.0, "Fern");
        CHECK(pt2.getPrice() == 20.0);
        CHECK(pt2.getName() == "Fern");
        CHECK(pt2.getType() == PLANT_TYPE::ORDER_PLANT);
    }
    SUBCASE("Copy Constructor") {
        PlantType pt3(25.0, "Cactus");
        PlantType pt4(pt3);
        CHECK(pt4.getPrice() == 25.0);
        CHECK(pt4.getName() == "Cactus");
        CHECK(pt4.getType() == PLANT_TYPE::ORDER_PLANT);
    }
    SUBCASE("Clone Method") {
        PlantType pt5(30.0, "Bonsai");
        PlantImplementor* ptClone = pt5.clone();
        PlantType* ptCloneCasted = dynamic_cast<PlantType*>(ptClone);
        REQUIRE(ptCloneCasted != nullptr);
        CHECK(ptCloneCasted->getPrice() == 30.0);
        CHECK(ptCloneCasted->getName() == "Bonsai");
        CHECK(ptCloneCasted->getType() == PLANT_TYPE::ORDER_PLANT);
        delete ptClone; // Clean up cloned object
    }
}

//TESTING COMPLETE Decorator chain with all decorators focusing on cloning and price calculation
TEST_CASE("Complete Decorator Chain Test Case") {
    SeedPacket* sp = new SeedPacket(10.0, "Orchid Seeds");
    Decoration* dec = new Decoration(5.0, "Glitter");
    Pot* pot = new Pot(15.0, "Elegant Pot");
    PlantType* pt = new PlantType(20.0, "Orchid Plant");
    pt->decorate(pot);
    pt->decorate(dec);
    pt->decorate(sp);
    CHECK(pt->getPrice() == 50.0); // 10 + 5 + 15 + 20
    // Clone the entire decoration chain
    PlantImplementor* ptClone = pt->clone();
    PlantType* ptCloneCasted = dynamic_cast<PlantType*>(ptClone);
    REQUIRE(ptCloneCasted != nullptr);
    CHECK(ptCloneCasted->getPrice() == 50.0);
    delete pt;
    delete ptClone;
}

//ADAPTER TESTS

#include "SeedPacketAdapter.h"
#include "PotAdapter.h"
#include "DecorationAdapter.h"

TEST_CASE("Adapter Pattern Test Cases") {
    SUBCASE("SeedPacketAdapter Test") {
        SeedPacketAdapter spa("Rose Seeds", 10.0);
        CHECK(spa.getPrice() == 10.0);
        CHECK(spa.getName() == "Rose Seeds");
        SeedPacketAdapter spa2(new SeedPacket(15.0, "Tulip Seeds"));
        CHECK(spa2.getPrice() == 15.0);
        CHECK(spa2.getName() == "Tulip Seeds");
        CHECK(spa2.getType() == PLANT_TYPE::SEED_PACKET);
        OrderPlant* op = spa2.getOrderPlant();
        REQUIRE(op != nullptr);
        CHECK(op->getPrice() == 15.0);
        CHECK(op->getName() == "Tulip Seeds");
        delete op;  // Clean up
    }
    SUBCASE("PotAdapter Test") {
        PotAdapter pa("Ceramic Pot", 15.0);
        CHECK(pa.getPrice() == 15.0);
        CHECK(pa.getName() == "Ceramic Pot");
        PotAdapter pa2(new Pot(20.0, "Plastic Pot"));
        CHECK(pa2.getPrice() == 20.0);
        CHECK(pa2.getName() == "Plastic Pot");
        CHECK(pa2.getType() == PLANT_TYPE::POT);
        OrderPlant* op = pa2.getOrderPlant();
        REQUIRE(op != nullptr);
        CHECK(op->getPrice() == 20.0);
        CHECK(op->getName() == "Plastic Pot");
        delete op;  // Clean up
    }
    SUBCASE("DecorationAdapter Test") {
        DecorationAdapter da("Glitter", 5.0);
        CHECK(da.getPrice() == 5.0);
        CHECK(da.getName() == "Glitter");
        DecorationAdapter da2(new Decoration(7.5, "Ribbons"));
        CHECK(da2.getPrice() == 7.5);
        CHECK(da2.getName() == "Ribbons");
        CHECK(da2.getType() == PLANT_TYPE::DECORATION);
        OrderPlant* op = da2.getOrderPlant();
        REQUIRE(op != nullptr);
        CHECK(op->getPrice() == 7.5);
        CHECK(op->getName() == "Ribbons");
        delete op;  // Clean up
    }
}

//TEST BRIDGE - testing plant class and plant implementor

#include "Plant.h"

TEST_CASE("Plant and plantimplementor tests") {
    SUBCASE("Plant from original creation") {
        Plant plant("Daisy", 20);
        CHECK(plant.getName() == "Daisy");
        CHECK(plant.getPrice() == 20);
        CHECK(plant.getType() == PLANT_TYPE::GREENHOUSE_PLANT);
        plant.convertToOrderType();
        CHECK(plant.getType() == PLANT_TYPE::ORDER_PLANT);
    }
    SUBCASE("Plant with Order plant implementor") {
        Plant plant(new PlantType(20, "Daisy"));
        CHECK(plant.getName() == "Daisy");
        CHECK(plant.getPrice() == 20);
        CHECK(plant.getType() == PLANT_TYPE::ORDER_PLANT);
    }
    SUBCASE("No implementor") {
        Plant plant;
        CHECK(plant.getName() == "Unnamed Plant");
        CHECK(plant.getPrice() == 0);
        CHECK(plant.getType() == PLANT_TYPE::GREENHOUSE_PLANT);
    }
    SUBCASE("Getting OrderPlant from Plant") {
        Plant plant(new PlantType(30, "Orchid"));
        OrderPlant* op = plant.getOrderPlant();
        REQUIRE(op != nullptr);
        CHECK(op->getName() == "Orchid");
        CHECK(op->getPrice() == 30);
        delete op; // Clean up
    }
}