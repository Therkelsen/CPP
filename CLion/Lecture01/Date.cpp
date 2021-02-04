
#include "Date.h"
#include<string>

Date::Date() {

    year = 0;
    month = 0;
    day = 0;

}

Date::Date(unsigned int year, unsigned int month, unsigned int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

unsigned int Date::getYear() const {
    return year;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getDay() const {
    return day;
}

void Date::setYear(unsigned int year) {
    this->year = year;
}

void Date::setMonth(unsigned int month) {
    this->month = month;
}

void Date::setDay(unsigned int day) {
    this->day = day;
}

std::string Date::getBirthday(){
    return std::to_string(getYear()) + "." + std::to_string(getMonth()) + "." + std::to_string(getDay());
}

void Date::reset(){
    year = 0;
    month = 0;
    day = 0;
}
