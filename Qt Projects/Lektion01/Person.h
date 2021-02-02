#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Date.h"

class Person {
public:
    Person();

    std::string getName() const;
    void setName(const std::string& name);

private:
    std::string mName;
    Date mDate;

};

#endif // PERSON_H
