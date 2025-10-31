#include "NurseryHub.h"
#include "Staff.h"
#include "Plant.h"
#include "GreenHousePlant.h"
#include "Customer.h"
#include "Command.h"
#include "Manager.h"
#include "ItemIterator.h"
#include "PlantImplementor.h"
#include "OrderBuilder.h"

#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>

using CommandPtr = std::shared_ptr<Command>;

NurseryHub::NurseryHub() : manager(nullptr), staff(nullptr) {
	NurseryHub::createMgr();
}

void NurseryHub::createMgr() {
	auto* mgr = new Manager("manager-1",this);
	manager = mgr;
	staff = manager;
}

NurseryHub::~NurseryHub() {
	if (manager)
		delete manager;
	manager = nullptr;
	staff = nullptr;
}

template <typename T>
static bool ptrPresent(const std::vector<T*>& vec, const T* p) {//helper to check if a raw pointer p is already in a std::vector
	return std::find(vec.begin(), vec.end(), p) !=vec.end();
}

/**
 * @file NurseryHub.cpp
 * @brief Implementation of the NurseryHub concrete mediator.
 *
 * Defines the routing logic for events/commands between nursery colleagues.
 */

/**
 * @brief Assign a command to an appropriate staff member.
 *
 * @note Part of the Mediator pattern—centralizes assignment logic
 * instead of letting colleagues reference each other directly.
 */
void NurseryHub::assign(CommandPtr cmd) {
	if (!cmd) {
		throw std::invalid_argument("Command cannot be null");
	}

	staff->receiveCommand(cmd);
}

/**
 * @brief Handle/broadcast an event from a colleague.
 *
 * @param sender Originator of the event (generic pointer).
 * @param event  Event key or type (e.g., "NEEDS_WATER", "ORDER_PLACED").
 * @param data   Optional payload (generic/opaque).
 *
 * @todo Route the event to interested colleagues (Staff, Customers).
 */
void NurseryHub::notify(void*, std::string, std::string) {
	//TODO: route/broadcast later
}

/**
 * @brief Register a plant with the mediator.
 */
void NurseryHub::registerPlant(Plant* p) {
	if (p && !ptrPresent(plants, p)) {
		plants.push_back(p);
	}
}

/**
 * @brief Register a staff member with the mediator.
 */
void NurseryHub::registerStaff(Staff* s) {
	if (s && staff) {
		s->addStaffMember(staff);
		staff = s;
	}
}

// bool NurseryHub::isCareBusy(const GreenHousePlant* p) const {
// 	if (p) {
//
// 		return p->getBusy();
//
// 	} else {
//
// 		return false;
// 	}
// }
//
// bool NurseryHub::wasLastCareSuccessful(const GreenHousePlant* p) const {
// 	if (p) {
//
// 		return p->getSuccess();
// 	} else {
//
// 		return false;
// 	}
// }

void NurseryHub::beginCare(GreenHousePlant* p, std::string type) {

	if (!p || !p->getIsAlive()) return;
	p->markCareStarted(type);
}

void NurseryHub::finishCare(GreenHousePlant* p, std::string type, bool success) {

	if (!p || !p->getIsAlive()) return;
	p->markCareFinished(success, type);
}

std::vector<std::string> NurseryHub::getPlantNamesByType(OrderBuilder* builder) const {
	std::vector<std::string> names;
	if (!builder) return names;
	names.reserve(plants.size());

	std::vector<Item*> items;
	items.reserve(plants.size());
	for (Plant* p : plants)
		items.push_back(static_cast<Item*>(p));

	ItemIterator it(items);
	for (it.first(); !it.isDone(); it.next()) {
		Item* item = it.currentItem();
		if (!item) continue;

		if (builder->checkType(item))
			names.push_back(item->getName());
	}
	return names;
}

// std::vector<std::string> NurseryHub::getPlantNamesByType(PLANT_TYPE type) const {
// 	std::vector<std::string> names;
// 	names.reserve(plants.size());
//
// 	//Convert vector<Plant*> -> vector<Item*>
// 	std::vector<Item*> items;
// 	items.reserve(plants.size());
// 	for (Plant* p : plants) {
// 		items.push_back(static_cast<Item*>(p));
// 	}
//
// 	ItemIterator it(items);
// 	for (it.first(); !it.isDone(); it.next()) {
// 		Item* item = it.currentItem();
// 		if (!item) {//currentItem() could be nullptr
// 			continue;
// 		}
// 		if (item->getType() == type) {
// 			names.push_back(item->getName());
// 		}
// 	}
// 	return names;
// }