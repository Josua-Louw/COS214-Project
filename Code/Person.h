#ifndef PERSON_H
#define PERSON_H

#include <string>

/**
 * @file Person.h
 * @brief Defines the Person class, a base class for staff in the Plant Nursery Simulator.
 * @details Provides a common interface for staff members, storing a unique identifier.
 */

/**
 * @class Person
 * @brief Abstract base class for entities with an identifier.
 * @details Stores a unique ID for staff members (e.g., PlantCaretaker, SalesManager).
 */
class Person {
protected:
    std::string id; /**< Unique identifier for the person. */
public:
    /**
     * @brief Constructs a Person with an ID.
     * @param id Unique identifier for the person.
     */
    Person(const std::string& id) : id(id) {}

    /**
     * @brief Gets the person's ID.
     * @return The ID as a string.
     */
    std::string getId() const { return id; }

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Person() = default;
};

#endif // PERSON_H