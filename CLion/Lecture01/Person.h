#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Date.h"

class Person {
private:
    std::string name;
    Date date;
    double age;
    double height;
    double weight;

public:
    Person();

    std::string getName() const;
    void setName(const std::string& name);

    void reset();

    double calcHatSize(double h, double m);

    double calcJacketSize(double h, double m, double age);

    double getAge();

    void setAge(double age);

    double getHeight();

    void setHeight(double h);

    double getWeight();

    void setWeight(double m);
};

#endif // PERSON_H
