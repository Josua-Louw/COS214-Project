#include "NurseryHub.h"

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
 *
 * @todo Implement selection strategy for which Staff will receive the command.
 */
void NurseryHub::assign(Command* cmd) {
	// TODO - implement NurseryHub::assign
	throw "Not yet implemented";
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
 *
 * @todo Add the plant to the internal registration for later routing and notifications.
 */
void NurseryHub::registerPlant(Plant* p) {
	// TODO - implement NurseryHub::registerPlant
	throw "Not yet implemented";
}

/**
 * @brief Register a staff member with the mediator.
 */
void NurseryHub::registerStaff(Staff* s) {
	// TODO - implement NurseryHub::registerStaff
	throw "Not yet implemented";
}
