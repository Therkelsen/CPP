//
// Created by Thomas Therkelsen on 27-05-2021.
//

#include "Materials.h"

Materials::Materials() : TimeAndMaterials() {

}

Materials::Materials(const std::string& description, double price) : TimeAndMaterials() {
    _description = description;
    _price = price;
}

double Materials::getPrice() const {
    return _price;
}

std::string Materials::getText() const {
    return _description;
}

void Materials::setDescription(const std::string& description) {
    _description = description;
}

void Materials::setPrice(double price) {
    _price = price;
}