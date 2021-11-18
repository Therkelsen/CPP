#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "Date.h"

class Person {
private:
    std::string name;
    Date date;
    double age;
    double height;
    double weight;
    std::string gender;
    double METs {0};

public:
    Person();

    void setName(const std::string& name);

    void setAge(double age);

    void setHeight(double h);

    void setWeight(double m);

    void setGender(std::string gender);

    std::string getName() const;

    double getAge();

    double getHeight();

    double getWeight();

    std::string getGender();

    double calcHatSize();

    double calcJacketSize();

    double calcWaistSize();

    double BMR();

    double caloriesBurnt(double MET, double m, double t);

    const std::string text[12][3] = {
            {"Number", "MET", "Description"},
            {"1", "1.3", "Sitting quietly and watching TV"},
            {"2", "2.0", "Playing the flute, sitting down"},
            {"3", "2.5", "Playing the violin, sitting down"},
            {"4", "3.5", "Fishing"},
            {"5", "4.3", "Walking 5.6 km/h (3.5 mph)"},
            {"6", "5.3", "Walking uphill 1-5% grade at 4.7 to 5.6 km/h (2.9-3.5 mph)"},
            {"7", "5.5", "Mowing lawn OR Ballroom dancing, fast"},
            {"8", "8.0", "Bicycling moderate 19 to 22 km/h (12-13.9 mph)"},
            {"9", "9.8", "Running 9.7km/h (6mph) OR Swimming, freestyle, fast"},
            {"10", "11.8", "Running 12 km/h (7.5mph)"},
            {"11", "12.8", "Running 14.5 km/h (9 mph)"}
    };

    void addMETs(double METs);

    double getMETs();
};

#endif // PERSON_H
