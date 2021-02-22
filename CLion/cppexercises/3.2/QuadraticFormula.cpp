//
// Created by Thomas Therkelsen on 09-02-2021.
//

#include "QuadraticFormula.h"
#include <cmath>
#include <string>

//  Constructor method
QuadraticFormula::QuadraticFormula(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = (b*b)-4*a*c;
}

//  Getter methods
double QuadraticFormula::getA() const {
    return a;
}

double QuadraticFormula::getB() const {
    return b;
}

double QuadraticFormula::getC() const {
    return c;
}

double QuadraticFormula::getDeterminant() const{
    return d;
}

//  Solves the quadratic formula and returns the solution
std::string QuadraticFormula::solve(){
    if (getDeterminant() == 0) {
        x1 = std::to_string((-b)/(2*a));
        solution = "x1 = " + x1;
        return solution;
    } else if (getDeterminant() > 0) {
        x1 = std::to_string((-b+sqrt(getDeterminant()))/(2*a));
        x2 = std::to_string((-b-sqrt(getDeterminant()))/(2*a));
        solution = "x1 = " + x1 + " | x2 = " + x2;
        return solution;
    } else if (getDeterminant() < 0) {
        x1 = std::to_string(-b/(2*a)) + " + " + std::to_string(sqrt(-1*getDeterminant())/(2*a)) + "i";
        x2 = std::to_string(-b/(2*a)) + " - " + std::to_string(sqrt(-1*getDeterminant())/(2*a)) + "i";
        solution = "x1 = " + x1 + " | x2 = " + x2;
        return solution;
    } else {
        return "You fucked up, this should not be possible";
    }
}
