
#include <iostream>
#include <ctime>
#include "./Date.h"
#include "./Person.h"

int main() {

    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    Person p1;
    Date d1 = Date();

    std::cout << "Hello World!" << std::endl;

    std::string name;
    std::cout << "What is your name?" << std::endl;
    getline(std::cin, name);

    p1.setName(name);

    unsigned int x;
    std::cout << "What is your birth year?" << std::endl;
    std::cin >> x;
    d1.setYear(x);

    std::cout << "What is your birth month?" << std::endl;
    std::cin >> x;
    d1.setMonth(x);

    std::cout << "What is your birth day?" << std::endl;
    std::cin >> x;
    d1.setDay(x);

    p1.setAge((timePtr->tm_year + 1900 - d1.getYear()) - 1);

    if (d1.getMonth() < timePtr->tm_mon + 1) {
        if (d1.getDay() < timePtr->tm_mday) {
            p1.setAge(p1.getAge() + 1);
        }
    }
    double y;
    std::cout << "What is your height?" << std::endl;
    std::cin >> y;
    p1.setHeight(y);

    std::cout << "What is your weight?" << std::endl;
    std::cin >> y;
    p1.setWeight(y);

    //printf("Name: %s\r\nBirthday: %s", p1.getName(), d1.getBirthday());
    std::cout << "Name: " << p1.getName() << std::endl;
    std::cout << "Birthdate: " << d1.getYear() << "." << d1.getMonth() << "." << d1.getDay() << std::endl;
    std::cout << "Age: " << p1.getAge() << "\n "<< std::endl;
    std::cout << "Height: " << p1.getHeight() << "\n "<< std::endl;
    std::cout << "Weight: " << p1.getWeight() << "\n "<< std::endl;

    std::cout << "Clothes: " << std::endl;
    std::cout << "Hat size: " << p1.calcHatSize(p1.getHeight(), p1.getWeight()) << std::endl;
    std::cout << "Jacket size: " << p1.calcJacketSize(p1.getHeight(), p1.getWeight(), p1.getAge()) << std::endl;

    return 0;
}
