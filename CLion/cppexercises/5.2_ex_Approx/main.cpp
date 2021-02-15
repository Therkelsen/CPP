#include <iostream>
#include "Ex.h"

int main() {
    Ex e1 = Ex();
    std::cout << e1.factorial(1) << std::endl;
    std::cout << e1.approxEx(3, 20) << std::endl;
    return 0;
}
