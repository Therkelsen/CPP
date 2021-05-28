#include <iostream>
#include <iomanip>
#include "WorkHours.h"
#include "Materials.h"

int main() {
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "-- Opgave 1 --" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    WorkHours* w1 = new WorkHours;
    WorkHours* w2 = new WorkHours(500);
    WorkHours* w3 = new WorkHours(500, 120);
    WorkHours* w4 = new WorkHours(500, 130, 2);
    WorkHours* w5 = new WorkHours(*w3);
    w2->setDescription("Mandetimer");
    w3->setDescription("Maskintimer");
    w4->setDescription("Overarbejdstimer");
    w5->setDescription("Ekstratimer");
    w5->setAmount(8);
    Materials* m1 = new Materials();
    Materials* m2 = new Materials("M\x9Btrik", 2);
    Materials* m3 = new Materials("Gevindstang", 30);
    m1->setDescription("Bolt");
    m1->setPrice(10);
    m1->setAmount(2);
    m2->setAmount(5);
    m3->setAmount(3);
    std::cout << std::right << std::setw(8) << "Antal" << " " << std::left << std::setw(40) << "Udf\x9Brt arbejde og materialeforbrug" <<
    std::right << std::setw(10) << "Pris" << std::setw(10) << "I alt" << std::endl;
    std::cout << *w1 << std::endl;
    std::cout << *w2 << std::endl;
    std::cout << *w3 << std::endl;
    std::cout << *w4 << std::endl;
    std::cout << *w5 << std::endl;
    std::cout << *m1 << std::endl;
    std::cout << *m2 << std::endl;
    std::cout << *m3 << std::endl;
    std::cout << std::endl << std::endl;
    return 0;
}
