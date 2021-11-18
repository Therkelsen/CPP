#include <cmath>
#include "Person.h"

//  This class contains solutions for 3.1, 3.3 & 3.4

Person::Person()
{

}

void Person::setName(const std::string& name) {
    this->name = name;
}

void Person::setAge(double age) {
    this->age = age;
}

void Person::setHeight(double h) {
    this->height = h;
}

void Person::setWeight(double m) {
    this->weight = m;
}

void Person::setGender(std::string gender) {
    this->gender = gender;
}

std::string Person::getName() const {
    return name;
}

double Person::getAge() {
    return age;
}

double Person::getHeight() {
    return height;
}

double Person::getWeight() {
    return weight;
}

std::string Person::getGender() {
    return gender;
}

double Person::calcHatSize() {
    return getWeight()/getHeight()*41.25*3.14;
}

double Person::calcJacketSize() {
    double size = (getHeight()*getWeight()/335);
    if (getAge() > 30) {
        double diff = getAge() - 30;
        size += diff/10 * 1/8;
    }
    return size;
}

double Person::calcWaistSize() {
    double size = (getWeight()/2.6);
    if (getAge() > 28) {
        double diff = getAge() - 28;
        size += diff/2 * 1/10;
    }
    return size;
}

double Person::BMR() {
    if (getGender() == "M") {
        return (10*getWeight()) + (6.25 * getHeight() - (5 * getAge()) + 5);
    } else {
        return (10*getWeight()) + (6.25 * getHeight() - (5 * getAge()) - 161);
    }
}

void Person::addMETs(double METs) {
    this->METs += METs;
}

double Person::getMETs() {
    return METs;
}



double Person::caloriesBurnt(double MET, double m, double t) {
    return MET * m * t;
}
