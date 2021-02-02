#include "Person.h"

Person::Person()
{

}

std::string Person::getName() const {
    return mName;
}

void Person::setName(const std::string& name) {
    mName = name;
}
