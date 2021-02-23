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
    std::string gender;

public:
    Person();

    void setName(const std::string& name);

    void setAge(double age);

    void setHeight(double h);

    void setWeight(double m);

    void setGender(std::string gender);

    std::string getName() const;

    double getAge();

    double getHeight();

    double getWeight();

    std::string getGender();

    double calcHatSize();

    double calcJacketSize();

    double calcWaistSize();

    double BMR();

};

#endif // PERSON_H
