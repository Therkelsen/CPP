//
// Created by Thomas Therkelsen on 27-05-2021.
//

#include "WorkHours.h"

WorkHours::WorkHours(double standardPrice) : TimeAndMaterials(1) {
    _standardPrice = standardPrice;
    _extraPrice = 0;
}

WorkHours::WorkHours(double standardPrice, double extraPrice) : TimeAndMaterials(1) {
    _standardPrice = standardPrice;
    _extraPrice = extraPrice;
}

WorkHours::WorkHours(double standardPrice, double extraPrice, int amount) : TimeAndMaterials(amount) {
    _standardPrice = standardPrice;
    _extraPrice = extraPrice;
}

double WorkHours::getPrice() const {
    return _standardPrice + _extraPrice;
}

std::string WorkHours::getText() const {
    return _text;
}

void WorkHours::setDescription(const std::string& text) {
    _text = text;
}

void WorkHours::setStandardPrice(double standardPrice) {
    _standardPrice = standardPrice;
}

void WorkHours::setExtraPrice(double extraPrice) {
    _extraPrice = extraPrice;
}