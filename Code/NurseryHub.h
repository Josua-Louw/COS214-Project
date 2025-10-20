#ifndef NURSERYHUB_H
#define NURSERYHUB_H

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
class NurseryHub : NurseryMediator {

private:
	vector<Plant*> plants;      ///< Plants registered with the mediator.
	vector<Staff*> staff;       ///< Staff members available for assignments.
	vector<customer*> customers;///< Customers interacting through the mediator.

public:
	/**
	 * @brief Assign a command to an appropriate staff member.
	 * @param cmd Command to route/dispatch.
	 */
	void assign(Command cmd);

	/**
	 * @brief Handle/broadcast an event from a colleague.
	 * @param sender Originator of the event (generic pointer).
	 * @param event  Event key or type.
	 * @param data   Optional payload.
	 *
	 * @todo Implement event routing/notification rules to colleagues.
	 */
	void notify(void sender, string event, any data);

	/**
	 * @brief Register a plant with the mediator so it can be tracked.
	 */
	void registerPlant(Plant* p);

	/**
	 * @brief Register a staff member with the mediator so it can receive assignments.
	 */
	void registerStaff(Staff* s);
};

#endif
