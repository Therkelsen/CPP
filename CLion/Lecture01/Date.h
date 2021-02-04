#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
public:
    Date();
    Date(unsigned int year, unsigned int month, unsigned int day);

    unsigned int getYear() const;   //get mYear
    unsigned int getMonth() const;  //get mMonth
    unsigned int getDay() const;    //get mDay

    void setYear(unsigned int year); //set mYear
    void setMonth(unsigned int month); //set mMonth
    void setDay(unsigned int day); //set mDay

    std::string getBirthday(); //return bday

    void reset();

private:
    unsigned int year, month, day;
};

#endif // DATE_H
