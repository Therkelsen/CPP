#include "Person.h"

Person::Person()
{

}

std::string Person::getName() const {
    return name;
}

void Person::setName(const std::string& name) {
    this->name = name;
}

void Person::reset() {

}