//
// Created by Thomas Therkelsen on 28-05-2021.
//

#include <ios>
#include <iomanip>
#include "TimeSheet.h"

TimeSheet::TimeSheet() : TimeAndMaterials() {

}

TimeSheet::~TimeSheet() {
    mItems.clear();
}

void TimeSheet::addTimeAndMaterial(TimeAndMaterials *tm) {
    mItems.push_back(tm);
}

double TimeSheet::getPrice() const {
    return TimeAndMaterials::getPrice();
}

std::string TimeSheet::getText() const {
    return TimeAndMaterials::getText();
}

void TimeSheet::sortByType() {

}

std::ostream &operator<<(std::ostream &ost, const TimeAndMaterials& tam) {
    ost << std::right << std::setw(8) << tam.getAmount() << " ";
    ost << std::left << std::setw(40) << tam.getText();
    ost << std::right << std::setw(10) << tam.totalPrice() << std::endl;
    return ost;
}