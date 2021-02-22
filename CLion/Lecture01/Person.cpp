#include <cmath>
#include "Person.h"

//  This class contains solutions for 3.1, 3.3, 3.4,

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
    name = "";
}

double Person::getAge() {
    return age;
}

void Person::setAge(double age) {
    this->age = age;
}

double Person::getHeight() {
    return height;
}

void Person::setHeight(double h) {
    this->height = h;
}

double Person::getWeight() {
    return weight;
}

void Person::setWeight(double m) {
    this->weight = m;
}

double Person::calcHatSize(double h, double m) {
    return m/h*41.25*3.14;
}

double Person::calcJacketSize(double h, double m, double age) {
    double size = (h*m/335);
    if (age > 30) {
        int diff = age - 30;
        size += diff/10 * 1/8;
    }
    return size;
}

double Person::calcWaistSize(double m) {
    double size = (m/2.6);
    if (age > 28) {
        int diff = age - 28;
        size += diff/2 * 1/10;
    }
    return size;
}