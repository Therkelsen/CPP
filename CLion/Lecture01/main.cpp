
#include <iostream>
#include <ctime>
#include "./Date.h"
#include "./Person.h"

int main() {

    time_t t = time(NULL);
    tm *timePtr = localtime(&t);

    Person p1;
    Date d1 = Date();

    std::string state = "1";

    std::cout << "==============================" << std::endl;

    while (std::stol(state) < 6) {
        switch (std::stol(state)) {
            case 1: {
                std::cout << "\nWelcome to the clothing size calculator" << std::endl;
                std::cout << "Press 2 to enter your details" << std::endl;
                std::cout << "Press 3 to get your basic info" << std::endl;
                std::cout << "Press 4 to get your clothing sizes" << std::endl;
                std::cout << "Press 5 to get your BMR" << std::endl;
                std::cout << "Press 6 to exit the program" << std::endl;
                getline(std::cin, state);
                break;
            }
            case 2: {
                std::string x;

                std::cout << "\nWhat is your name?" << std::endl;
                getline(std::cin, x);
                p1.setName(x);

                std::cout << "What is your birth year? (YYYY)" << std::endl;
                getline(std::cin, x);
                d1.setYear(std::stol(x));

                std::cout << "What is your birth month? (MM)" << std::endl;
                getline(std::cin, x);
                d1.setMonth(std::stol(x));

                std::cout << "What is your birth day? (DD)" << std::endl;
                getline(std::cin, x);
                d1.setDay(std::stol(x));

                p1.setAge((timePtr->tm_year + 1900 - d1.getYear()) - 1);

                if (d1.getMonth() < timePtr->tm_mon + 1) {
                    if (d1.getDay() < timePtr->tm_mday) {
                        p1.setAge(p1.getAge() + 1);
                    }
                }
                std::string y;
                std::cout << "What is your height? (In centimeters)" << std::endl;
                getline(std::cin, y);
                p1.setHeight(std::stol(y));

                std::cout << "What is your weight? (In kilograms)" << std::endl;
                getline(std::cin, y);
                p1.setWeight(std::stol(y));

                std::cout << "What is your gender? (Note, only M or F are valid inputs)" << std::endl;
                getline(std::cin, y);
                if (y == "M" || y == "F") {
                    p1.setGender(y);
                } else {
                    std::cout << "\nYou dumbass, I specifically told you ONLY \"M\" and \"F\" are valid inputs!" << std::endl;
                    std::cout << "Press 2 to enter your details" << std::endl;
                    std::cout << "Press 3 to get your basic info" << std::endl;
                    std::cout << "Press 4 to get your clothing sizes" << std::endl;
                    std::cout << "Press 5 to get your BMR" << std::endl;
                    std::cout << "Press 6 to exit the program" << std::endl;
                    getline(std::cin, state);
                    break;
                }

                std::cout << "\nWelcome to the clothing size calculator" << std::endl;
                std::cout << "Press 2 to enter your details" << std::endl;
                std::cout << "Press 3 to get your basic info" << std::endl;
                std::cout << "Press 4 to get your clothing sizes" << std::endl;
                std::cout << "Press 5 to get your BMR" << std::endl;
                std::cout << "Press 6 to exit the program" << std::endl;
                getline(std::cin, state);
                break;
            }

            case 3: {
                std::cout << "\nName: " << p1.getName() << std::endl;
                std::cout << "Birthday: " << d1.getBirthday() << std::endl;
                std::cout << "Age: " << p1.getAge() << std::endl;
                std::cout << "Height: " << p1.getHeight() << std::endl;
                std::cout << "Weight: " << p1.getWeight() << std::endl;

                std::cout << "\nWelcome to the clothing size calculator" << std::endl;
                std::cout << "Press 2 to enter your details" << std::endl;
                std::cout << "Press 3 to get your basic info" << std::endl;
                std::cout << "Press 4 to get your clothing sizes" << std::endl;
                std::cout << "Press 5 to get your BMR" << std::endl;
                std::cout << "Press 6 to exit the program" << std::endl;
                getline(std::cin, state);
                break;
            }

            case 4: {
                std::cout << "\nClothes: " << std::endl;
                std::cout << "Hat size: " << p1.calcHatSize() << std::endl;
                std::cout << "Jacket size: " << p1.calcJacketSize() << std::endl;

                std::cout << "\nWelcome to the clothing size calculator" << std::endl;
                std::cout << "Press 2 to enter your details" << std::endl;
                std::cout << "Press 3 to get your basic info" << std::endl;
                std::cout << "Press 4 to get your clothing sizes" << std::endl;
                std::cout << "Press 5 to get your BMR" << std::endl;
                std::cout << "Press 6 to exit the program" << std::endl;
                getline(std::cin, state);
                break;
            }

            case 5: {
                std::cout << "\nYour Basal Metabolic Rate is: " << std::endl;
                std::cout << p1.BMR() << std::endl;

                std::cout << "\nWelcome to the clothing size calculator" << std::endl;
                std::cout << "Press 2 to enter your details" << std::endl;
                std::cout << "Press 3 to get your basic info" << std::endl;
                std::cout << "Press 4 to get your clothing sizes" << std::endl;
                std::cout << "Press 5 to get your BMR" << std::endl;
                std::cout << "Press 6 to exit the program" << std::endl;
                getline(std::cin, state);
                break;
            }

            default: {
                break;
            }
        }

    }

    std::cout << "Exiting program" << std::endl;
    return 0;
}
