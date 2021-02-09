//
// Created by Thomas Therkelsen on 09-02-2021.
//

#include "QuadraticFormula.h"
#include <cmath>
#include <string>

QuadraticFormula::QuadraticFormula(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = (b*b)-4*a*c;
}

double QuadraticFormula::getA() {
    return a;
}

double QuadraticFormula::getB() {
    return b;
}

double QuadraticFormula::getC() {
    return c;
}

double QuadraticFormula::getDeterminant(){
    return d;
}

std::string QuadraticFormula::solve1(){
    if(d > 0) {
        return std::to_string((-b+d)/2*d);
    } else {
        return std::to_string((-b+d)/2*d) + "i";
    }
}

std::string QuadraticFormula::solve2(){
    if(d > 0) {
        return std::to_string((-b-d)/2*d);
    } else {
        return std::to_string((-b-d)/2*d) + "i";
    }
}
