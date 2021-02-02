#ifndef DATE_H
#define DATE_H


class Date {
public:
    Date();

    unsigned int getYear() const;   //get mYear
    unsigned int getMonth() const;  //get mMonth
    unsigned int getDay() const;    //get mDay

    void setYear(unsigned int year); //set mYear
    void setMonth(unsigned int month); //set mMonth
    void setDay(unsigned int day); //set mDay

private:
    unsigned int mYear, mMonth, mDay;

};

#endif // DATE_H
