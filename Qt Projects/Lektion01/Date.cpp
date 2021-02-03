#include "Date.h"



Date::Date() {

    mYear = 0;
    mMonth = 0;
    mDay = 0;

}

Date::Date(unsigned int year, unsigned int month, unsigned int day) {
    mYear = year;
    mMonth = month;
    mDay = day;
}

unsigned int Date::getYear() const {
    return mYear;
}

unsigned int Date::getMonth() const {
    return mMonth;
}

unsigned int Date::getDay() const {
    return mDay;
}

void Date::setYear(unsigned int year) {
    mYear = year;
}

void Date::setMonth(unsigned int month) {
    mMonth = month;
}

void Date::setDay(unsigned int day) {
    mDay = day;
}

std::string Date::getBirthday(){
    return std::to_string(getYear()) + "." + std::to_string(getMonth()) + "." + std::to_string(getDay());
}
