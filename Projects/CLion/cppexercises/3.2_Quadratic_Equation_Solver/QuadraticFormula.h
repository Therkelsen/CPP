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
    std::string x1;
    std::string x2;

public:

    double getDeterminant() const;

    std::string solve1();
    std::string solve2();

    QuadraticFormula(double a, double b, double c);

    double getA() const;

    double getB() const;

    double getC() const;

    std::string solve();
};


#endif //CPPEXERCISES_3_2_QUADRATICFORMULA_H
