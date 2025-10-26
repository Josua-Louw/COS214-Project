#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
private:
    std::string name;
public:
    Person(const std::string& name) : name(name) {}
    std::string getName() const {
        return this->name;
    }
};

#endif
