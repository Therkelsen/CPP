//
// Created by Thomas Therkelsen on 27-05-2021.
//

#include <ios>
#include <iomanip>
#include "TimeAndMaterials.h"

TimeAndMaterials::TimeAndMaterials() {
    mAmount = 1;
}

TimeAndMaterials::TimeAndMaterials(double amount) {
    mAmount = amount;
}

std::string TimeAndMaterials::getText() const {
    return mText;
}

double TimeAndMaterials::getPrice() const {
    return mPrice;
}

std::ostream &operator<<(std::ostream &ost, const TimeAndMaterials& tam) {
    ost << std::right << std::setw(8) << tam.getAmount() << " ";
    ost << std::left << std::setw(40) << tam.getText();
    ost << std::right << std::setw(10) << tam.getPrice() << std::setw(10) << tam.totalPrice() << std::endl;
    return ost;
}

