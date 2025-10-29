#ifndef NURSERYMEDIATOR_H
#define NURSERYMEDIATOR_H

#include <string>
#include <memory>

class Command;
class GreenHousePlant;
class Plant;
class Staff;
class Customer;
using CommandPtr = std::shared_ptr<Command>;
/**
 * @file NurseryMediator.h
 * @brief Abstract mediator interface for coordinating communication in the nursery.
 *
 * The mediator decouples colleagues (e.g., Staff, Customer, GreenHouse) by routing
 * events and commands between them. Colleagues interact with the mediator instead
 * of referencing each other directly.
 */

/**
 * @class NurseryMediator
 * @brief Abstract Mediator in the Mediator design pattern.
 *
 * Declares the operations used by colleagues to notify the mediator about events
 * and to request assignments. Concrete mediator (NurseryHub) implement how events are routed and how commands are assigned.
 */
class NurseryMediator {

public:
	virtual ~NurseryMediator() = default;
	/**
	 * @brief Broadcast or route an event reported by a colleague.
	 * @param sender Originator of the event (generic pointer from the caller).
	 * @param event  Event key or type (e.g., "CARE_REQUEST", "ORDER_PLACED").
	 * @param data   Optional payload (generic/opaque).
	 *
	 * @note Signatures intentionally follow the class diagram. Implementation
	 * details like types/ownership are defined in the concrete mediator.
	 */

	/**
	 * @note This function's parameters will need to be changed to work on different data types.
	 * @todo Modify the parameters to use appropriate types instead of generic pointers.
	 * @example Change 'void* sender' to a specific class pointer, and 'std::string data' to a more suitable type.
	 * We can use overloading to have the notify work on plants or on staff or on customers specifically.
	 */
	virtual void notify(void* sender, std::string event, std::string data) = 0;

	/**
	 * @brief Assign a command via the mediator to an appropriate colleague.
	 * @param cmd Command to be routed/assigned.
	 */
	virtual void assign(CommandPtr cmd) = 0;

	/**
	 * @brief Register a plant with the mediator.
	 * @param p Plant to be tracked and considered for routing/notifications.
	 */
	virtual void registerPlant(Plant* p) = 0;

	/**
	 * @brief Register a staff member with the mediator.
	 * @param s Staff member available for assignments/notifications.
	 */
	virtual void registerStaff(Staff* s) = 0;

	//GreenHousePlant functions
	// virtual bool isCareBusy(const GreenHousePlant* p) const = 0;
	// virtual bool wasLastCareSuccessful(const GreenHousePlant* p) const = 0;
	virtual void beginCare(GreenHousePlant* p, std::string type) = 0;               //caretaker grabbed job
	virtual void finishCare(GreenHousePlant* p, std::string type, bool success) =0;//timer for command completed
};

#endif
