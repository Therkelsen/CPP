#include <iostream>
#include <iomanip>
#include <cmath>
#include "Pi.h"

int main() {
    Pi p1 = Pi();
    int n = 100000;
    std::cout << std::fixed << std::showpoint;
    for (int i = 1; i <= n; i++) {
        std::cout << "Fraction No.: " << std::setw(5) << i << std::setw(10) << "  |  Pi Approx.: "
                  << std::setw(8) << std::setprecision(5) << p1.approximatePi(i) << std::endl;
    }

    std::cout << "\nApprox. of Pi at " << n << " fractions: " << std::setprecision(5) << p1.piApproximated << std::endl;
    std::cout << "Actual Pi: " << std::setw(8) << std::setprecision(5) << p1.pi << std::endl;
    std::cout << "Error %: " << std::setw(10) << std::setprecision(5) << (double)(100-(p1.piApproximated/p1.pi*100)) << "%" << std::endl;
}
