//
// Created by Thomas Therkelsen on 09-02-2021.
//

#ifndef CPPEXERCISES_3_2_QUADRATICFORMULA_H
#define CPPEXERCISES_3_2_QUADRATICFORMULA_H

#include <string>

class QuadraticFormula {
private:

    double a{};
    double b{};
    double c{};
    double d{};

    std::string solution;

public:

    double getDeterminant();

    std::string solve1();
    std::string solve2();

    QuadraticFormula(double a, double b, double c);

    double getA();

    double getB();

    double getC();

    std::string solve();
};


#endif //CPPEXERCISES_3_2_QUADRATICFORMULA_H
