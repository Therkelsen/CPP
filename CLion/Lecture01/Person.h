#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Date.h"

class Person {
public:
    Person();

    std::string getName() const;
    void setName(const std::string& name);

    void reset();

private:
    std::string name;
    Date date;
};

#endif // PERSON_H
