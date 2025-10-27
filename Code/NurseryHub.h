#ifndef NURSERYHUB_H
#define NURSERYHUB_H

#include <vector>
#include <string>
#include "NurseryMediator.h"

class Command;
class GreenHousePlant;
class Plant;
class Staff;
class Customer;

/**
 * @file NurseryHub.h
 * @brief Concrete mediator coordinating plants, staff and customers in the nursery.
 *
 * Holds collections of colleagues and implements the routing logic for events
 * and commands between them.
 */

/**
 * @class NurseryHub
 * @brief Concrete Mediator implementation.
 *
 * Maintains registries of plants, staff, and customers. Implements the
 * `notify`, `assign`, and registration operations declared by NurseryMediator.
 */
class NurseryHub : public NurseryMediator {

private:
	std::vector<Plant*> plants;      ///< Plants registered with the mediator.
	std::vector<Staff*> staff;       ///< Staff members available for assignments.
	std::vector<Customer*> customers;///< Customers interacting through the mediator.

public:
	NurseryHub();
	/**
	 * @brief Assign a command to an appropriate staff member.
	 * @param cmd Command to route/dispatch.
	 */
	void assign(Command* cmd) override;

	/**
	 * @brief Handle/broadcast an event from a colleague.
	 * @param sender Originator of the event (generic pointer).
	 * @param event  Event key or type.
	 * @param data   Optional payload.
	 *
	 * @todo Implement event routing/notification rules to colleagues.
	 */
	void notify(void* sender, std::string event, std::string data) override;

	/**
	 * @brief Register a plant with the mediator so it can be tracked.
	 */
	void registerPlant(Plant* p) override;

	/**
	 * @brief Register a staff member with the mediator so it can receive assignments.
	 */
	void registerStaff(Staff* s) override;

	bool isCareBusy(const GreenHousePlant* p) const override;
	bool wasLastCareSuccessful(const GreenHousePlant* p) const override;
	void beginCare(GreenHousePlant* p) override;
	void finishCare(GreenHousePlant* p, bool success) override;
};

#endif
