#include <iostream>
#include <cmath>
#include "./QuadraticFormula.h"

int main() {

    QuadraticFormula q1 = QuadraticFormula(2,1,1);

    std::cout << "a = " << q1.getA() << " | b = " << q1.getB() << " | c = " << q1.getC() << " | d = " << q1.getDeterminant() << std::endl;
    std::cout << "Solution: " << q1.solve() << std::endl;

    return 0;
}
