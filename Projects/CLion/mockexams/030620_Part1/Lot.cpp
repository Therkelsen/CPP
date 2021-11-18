//
// Created by Thomas Therkelsen on 28-05-2021.
//

#include <ios>
#include <iomanip>
#include "Lot.h"

Lot::Lot() {}

Lot::Lot(const std::string& address, double minPrice, int size) {
    mAddress = address;
    mMinPrice = minPrice;
    mSize = size;
}

int Lot::getSize() const {
    return mSize;
}

double Lot::getMinimumPrice() const {
    return mMinPrice;
}

std::string Lot::getAddress() const {
    return mAddress;
}

void Lot::setSize(int size) {
    mSize = size;
}

void Lot::setMinimumPrice(double price) {
    mMinPrice = price;
}

void Lot::setAddress(const std::string& address) {
    mAddress = address;
}

std::ostream &operator<<(std::ostream &ost, const Lot &l) {
    ost << std::left << std::setw(20) << l.getAddress();
    ost << std::right << std::setw(9) << l.getMinimumPrice();
    ost << std::right << std::setw(6) << l.getSize();
    return ost;
}

std::istream &operator>>(std::istream &ist, Lot &l) {
    std::string address;
    std::getline(ist, address, ';');
    //std::cerr << "Address: " << address << std::endl;

    std::string temp;
    std::getline(ist, temp, ';');
    //std::cerr << "Minimum price: " << temp << std::endl;
    double minPrice = std::stod(temp);

    std::getline(ist, temp);
    //std::cerr << "Size: " << temp << std::endl;
    int size = std::stoi(temp);

    l.setAddress(address);
    l.setSize(size);
    l.setMinimumPrice(minPrice);
W
    return ist;
}
