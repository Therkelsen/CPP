
#include <iostream>
#include <ctime>
#include "./Date.h"
#include "./Person.h"

int main() {
    time_t t = time(NULL);
    tm *timePtr = localtime(&t);

    Person p1;
    Date d1 = Date();

    std::string state;

    while (std::stoul(state) < 5) {
        switch (std::stoul(state)) {
            case 1: {
                std::string x;

                std::cout << "What is your name?" << std::endl;
                getline(std::cin, x);
                p1.setName(x);

                std::cout << "What is your birth year?" << std::endl;
                getline(std::cin, x);
                d1.setYear(std::stoul(x));

                std::cout << "What is your birth month?" << std::endl;
                std::cin >> x;
                d1.setMonth(std::stoul(x));

                std::cout << "What is your birth day?" << std::endl;
                std::cin >> x;
                d1.setDay(std::stoul(x));

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

                state = "99";
                break;
            }

            case 2: {
                std::cout << "Name: " << p1.getName() << std::endl;
                std::cout << "Birthdate: " << d1.getYear() << "." << d1.getMonth() << "." << d1.getDay() << std::endl;
                std::cout << "Age: " << p1.getAge() << "\n " << std::endl;
                std::cout << "Height: " << p1.getHeight() << "\n " << std::endl;
                std::cout << "Weight: " << p1.getWeight() << "\n " << std::endl;

                state = "99";
                break;
            }

            case 3: {
                std::cout << "Clothes: " << std::endl;
                std::cout << "Hat size: " << p1.calcHatSize(p1.getHeight(), p1.getWeight()) << std::endl;
                std::cout << "Jacket size: " << p1.calcJacketSize(p1.getHeight(), p1.getWeight(), p1.getAge())
                          << std::endl;

                state = "99";
                break;
            }

            case 4: {
                break;
            }

            case 5: {
                break;
            }

            default: {
                std::cout << "Welcome to the clothing size calculator" << std::endl;
                std::cout << "Press 1 to enter your details" << std::endl;
                std::cout << "Press 2 to get your basic info" << std::endl;
                std::cout << "Press 3 to get your clothing sizes" << std::endl;
                std::cout << "Press 4 to exit the program" << std::endl;
                getline(std::cin, state);
                break;
            }
        }
    }

    std::cout << "Exiting program" << std::endl;
    return 0;
}
