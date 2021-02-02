#include <iostream>
#include "Date.h"
#include "Person.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Date d1;
    d1.setYear(2000);
    d1.setMonth(12);
    d1.setDay(19);
    std::cout << "Dato: " << d1.getYear() << "." << d1.getMonth() << "." << d1.getDay() << std::endl;

    Person p1;
    p1.setName("Thomas Therkelsen");
    std::cout << "Navn: " << p1.getName() << std::endl;

    return 0;
}
