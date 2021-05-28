//
// Created by Thomas Therkelsen on 27-05-2021.
//

#ifndef INC_170820_PART1_TIMEANDMATERIALS_H
#define INC_170820_PART1_TIMEANDMATERIALS_H

#include <string>

class TimeAndMaterials {
public:
    TimeAndMaterials();
    TimeAndMaterials(double amount);
    virtual ~TimeAndMaterials() = default;
    double getAmount() const { return mAmount; }

    virtual double getPrice() const = 0;
    virtual std::string getText() const = 0;
    virtual double totalPrice() const { return getAmount()*getPrice(); }

    void setAmount(double amount) { mAmount = amount; }

    friend std::ostream& operator<<(std::ostream& ost, const TimeAndMaterials& tam);

private:
    double mAmount, mPrice;
    std::string mText;
};

std::ostream& operator<<(std::ostream& ost, const TimeAndMaterials& tam);

#endif //INC_170820_PART1_TIMEANDMATERIALS_H
