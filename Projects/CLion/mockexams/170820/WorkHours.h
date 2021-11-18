//
// Created by Thomas Therkelsen on 27-05-2021.
//

#ifndef INC_170820_PART1_WORKHOURS_H
#define INC_170820_PART1_WORKHOURS_H

#include "TimeAndMaterials.h"

class WorkHours : public TimeAndMaterials {
public:
    WorkHours(double standardPrice = 0);
    WorkHours(double standardPrice, double extraPrice);
    WorkHours(double standardPrice, double extraprice, int amount);
    double getPrice() const;
    std::string getText() const;
    void setStandardPrice(double standardPrice);
    void setExtraPrice(double extraPrice);
    void setDescription(const std::string &text);
    double getAmount() const;

private:
    double _standardPrice, _extraPrice;
    std::string _text;
};

#endif //INC_170820_PART1_WORKHOURS_H
