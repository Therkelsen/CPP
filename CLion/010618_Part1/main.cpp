#include <iostream>
#include "Box.h"

int main() {
    Box<double> b1(5);
    Box<double> b2(10);
    Box<double> b3 = b1;
    Box<double> b4(b1);
    b1 = b2;
    std::cout << "b1.size() = " << b1.size() << std::endl;
    std::cout << "b2.size() = " << b2.size() << std::endl;
    std::cout << "b3.size() = " << b3.size() << std::endl;
    std::cout << "b4.size() = " << b4.size() << std::endl;
    return 0;
}
