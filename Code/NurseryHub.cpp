#include "NurseryHub.h"
#include "Staff.h"
#include "Plant.h"
#include "GreenHousePlant.h"
#include "Customer.h"
#include "Command.h"

#include <algorithm>
#include <vector>

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
void NurseryHub::assign(Command* cmd) {
	if (!cmd) {
		return;
	}
	//Try Chain-of-Responsibility entry points first
	for (Staff* s : staff) {
		if (s && s->handleRequest(cmd)) return;
	}
	//Fallback(just hand it to the first available staff)
	for (Staff* s : staff) {
		if (s) { s->receiveCommand(cmd); return;}
	}
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
void NurseryHub::notify(void* sender, std::string event, std::string data) {
	// TODO - implement NurseryHub::notify
	throw "Not yet implemented";
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
	if (s && !ptrPresent(staff, s)) {
		staff.push_back(s);
	}
}

bool NurseryHub::isCareBusy(const GreenHousePlant* p) const {
	if (p) {
		return p->getBusy();
	} else {
		return false;
	}
}

bool NurseryHub::wasLastCareSuccessful(const GreenHousePlant* p) const {
	if (p) {
		return p->getSuccess();
	} else {
		return false;
	}
}

void NurseryHub::beginCare(GreenHousePlant* p) {
	if (!p) return;
	p->markCareStarted();
}

void NurseryHub::finishCare(GreenHousePlant* p, bool success) {
	if (!p) return;
	p->markCareFinished(success);
}