
#include <iostream>
#include <ctime>
#include <iomanip>
#include "./Date.h"
#include "./Person.h"

using namespace std;

void printOptions(){
    cout << "\nWelcome to the clothing size calculator" << endl;
    cout << "Press 2 to enter your details" << endl;
    cout << "Press 3 to get your basic info" << endl;
    cout << "Press 4 to get your clothing sizes" << endl;
    cout << "Press 5 to get your BMR" << endl;
    cout << "Press 6 to exit the program" << endl;
}

string sep = "  |  ";

int main() {

    time_t t = time(NULL);
    tm *timePtr = localtime(&t);

    Person p1;
    Date d1 = Date();

    string state = "1";

    cout << "==============================" << endl;

    while (stol(state) < 6) {
        switch (stol(state)) {
            case 1: {
                printOptions();
                getline(cin, state);
                break;
            }
            case 2: {
                string x;

                /*cout << "\nWhat is your name?" << endl;
                getline(cin, x);
                p1.setName(x);

                cout << "What is your birth year? (YYYY)" << endl;
                getline(cin, x);
                d1.setYear(stol(x));

                cout << "What is your birth month? (MM)" << endl;
                getline(cin, x);
                d1.setMonth(stol(x));

                cout << "What is your birth day? (DD)" << endl;
                getline(cin, x);
                d1.setDay(stol(x));

                p1.setAge((timePtr->tm_year + 1900 - d1.getYear()) - 1);

                if (d1.getMonth() < timePtr->tm_mon + 1) {
                    if (d1.getDay() < timePtr->tm_mday) {
                        p1.setAge(p1.getAge() + 1);
                    }
                }
                string y;
                cout << "What is your height? (In centimeters)" << endl;
                getline(cin, y);
                p1.setHeight(stol(y));

                cout << "What is your weight? (In kilograms)" << endl;
                getline(cin, y);
                p1.setWeight(stol(y));

                cout << "What is your gender? (Note, only M or F are valid inputs)" << endl;
                getline(cin, y);
                if (y == "M" || y == "F") {
                    p1.setGender(y);
                } else if (y == "m") {
                    p1.setGender("M");
                } else if (y == "f") {
                    p1.setGender("F");
                } else {
                    cout << "\nYou dumbass, I specifically told you ONLY \"M\" and \"F\" are valid inputs!" << endl;
                    printOptions();
                    getline(cin, state);
                    break;
                }*/

                cout << "How active were you today?"                                                                                << endl;
                cout << "Press the number that corresponds\nto the activities you did today."                                       << endl;
                cout << "Hit 0 when you are done entering your\ninfo or weren't active today\n"                                     << endl;
                cout <<               p1.text[0][0]  << sep << setw(4) << p1.text[0][1]  << sep <<                p1.text[0][2]  << endl;
                cout << setw(6) << p1.text[1][0]  << sep << setw(4) << p1.text[1][1]  << sep << setw(31) << p1.text[1][2]  << endl;
                cout << setw(6) << p1.text[2][0]  << sep << setw(4) << p1.text[2][1]  << sep << setw(31) << p1.text[2][2]  << endl;
                cout << setw(6) << p1.text[3][0]  << sep << setw(4) << p1.text[3][1]  << sep << setw(32) << p1.text[3][2]  << endl;
                cout << setw(6) << p1.text[4][0]  << sep << setw(4) << p1.text[4][1]  << sep << setw(7)  << p1.text[4][2]  << endl;
                cout << setw(6) << p1.text[5][0]  << sep << setw(4) << p1.text[5][1]  << sep << setw(26) << p1.text[5][2]  << endl;
                cout << setw(6) << p1.text[6][0]  << sep << setw(4) << p1.text[6][1]  << sep << setw(58) << p1.text[6][2]  << endl;
                cout << setw(6) << p1.text[7][0]  << sep << setw(4) << p1.text[7][1]  << sep << setw(37) << p1.text[7][2]  << endl;
                cout << setw(6) << p1.text[8][0]  << sep << setw(4) << p1.text[8][1]  << sep << setw(46) << p1.text[8][2]  << endl;
                cout << setw(6) << p1.text[9][0]  << sep << setw(4) << p1.text[9][1]  << sep << setw(51) << p1.text[9][2]  << endl;
                cout << setw(6) << p1.text[10][0] << sep <<               p1.text[10][1] << sep << setw(23) << p1.text[10][2] << endl;
                cout << setw(6) << p1.text[11][0] << sep <<               p1.text[11][1] << sep << setw(24) << p1.text[11][2] << endl;
                string input;
                double METs {0};
                while (input != "COMPLETELY DONE TAKING INPUTS FOR METS") {
                    getline(cin, input);
                    if (stoi(input) == 0) {
                        p1.addMETs(METs);
                        p1.caloriesBurnt(p1.getMETs(), p1.getWeight());
                        input = "COMPLETELY DONE TAKING INPUTS FOR METS";
                        break;
                    } else {
                        METs += stoi(input);
                        input = "";
                    }
                }
                printOptions();
                getline(cin, state);
                break;
            }

            case 3: {

                break;
            }

            case 4: {
                cout << "\nName: " << p1.getName() << endl;
                cout << "Birthday: " << d1.getBirthday() << endl;
                cout << "Age: " << p1.getAge() << endl;
                cout << "Height: " << p1.getHeight() << endl;
                cout << "Weight: " << p1.getWeight() << endl;

                printOptions();
                getline(cin, state);
                break;
            }

            case 5: {
                cout << "\nClothes: " << endl;
                cout << "Hat size: " << p1.calcHatSize() << endl;
                cout << "Jacket size: " << p1.calcJacketSize() << endl;

                printOptions();
                getline(cin, state);
            }

            case 6: {
                cout << "\nYour Basal Metabolic Rate is: " << endl;
                cout << p1.BMR() << endl;

                printOptions();
                getline(cin, state);
                break;
            }

            default: {
                break;
            }
        }

    }

    cout << "Exiting program" << endl;
    return 0;
}
