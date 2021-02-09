#include <iostream>
#include <cmath>
#include "./QuadraticFormula.h"

int main() {

    QuadraticFormula q1 = QuadraticFormula(1,2,3);

    std::cout << "A: " << q1.getA() << std::endl;
    std::cout << "B: " << q1.getB() << std::endl;
    std::cout << "C: " << q1.getC() << std::endl;
    std::cout << "D: " << ((q1.getB()*q1.getB())-4*q1.getA()*q1.getC()) << std::endl;
    std::cout << "Determinant: " << q1.getDeterminant() << std::endl;
    std::cout << "X1: " << q1.solve1() << std::endl;
    std::cout << "X2: " << q1.solve2() << std::endl;

    return 0;
}
