#include <iostream>
#include <cmath>
#include "./QuadraticFormula.h"

int main() {

    int state {1};
    double a,b,c;

    while (state == 1) {
        std::cout << "Please enter your variable values for 2nd degree equation" << std::endl;
        std::cout << "Enter a:" << std::endl;
        std::cin >> a;
        std::cout << "Enter b:" << std::endl;
        std::cin >> b;
        std::cout << "Enter c:" << std::endl;
        std::cin >> c;

        QuadraticFormula q1 = QuadraticFormula(a, b, c);

        std::cout << "a = " << q1.getA() << " | b = " << q1.getB() << " | c = " << q1.getC() << " | d = "
                  << q1.getDeterminant() << std::endl;
        std::cout << "Solution: " << q1.solve() << std::endl;

        std::string choice = "no choice yet";
        while (choice != "n" && choice != "y") {
            std::cout << "\nDo you want to solve another 2nd degree equation?" << std::endl;
            std::cout << "Press y or n" << std::endl;
            std::cin >> choice;
            if (choice == "n" || choice == "y") {
                break;
            }
        }
        if (choice == "n") {
            break;
        }
    }

    return 0;
}
