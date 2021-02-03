#include <iostream>
#include "Date.h"
#include "Person.h"

using namespace std;

int main() {
    Person p1;
    Date d1 = Date();

    cout << "Hello World!" << endl;

    std::string name;
    cout << "What is your name?" << endl;
    cin >> name;

    p1.setName(name);

    unsigned int x;
    cout << "What is your birth year?" << endl;
    cin >> x;
    d1.setYear(x);

    cout << "What is your birth month?" << endl;
    cin >> x;
    d1.setMonth(x);

    cout << "What is your birth day?" << endl;
    cin >> x;
    d1.setDay(x);

    printf("Name: %s\r\nBirthday: %s", p1.getName(), d1.getBirthday());
    /*cout << "Name: " << p1.getName() << endl;
    cout << "Date: " << d1.getYear() << "." << d1.getMonth() << "." << d1.getDay() << endl;*/

    return 0;
}
