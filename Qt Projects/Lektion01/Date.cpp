#include "Date.h"

Date::Date() {

    mYear = 0;
    mMonth = 0;
    mDay = 0;

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
