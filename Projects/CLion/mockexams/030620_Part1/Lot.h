//
// Created by Thomas Therkelsen on 28-05-2021.
//

#ifndef INC_030620_PART1_LOT_H
#define INC_030620_PART1_LOT_H

#include <string>

class Lot {
public:
    Lot();
    Lot(const std::string& address, double minPrice, int size);
    int getSize() const;
    double getMinimumPrice() const;
    std::string getAddress() const;
    void setSize(int size);
    void setMinimumPrice(double price);
    void setAddress(const std::string& address);

    friend std::ostream& operator<<(std::ostream& ost, const Lot& l);

    friend std::istream& operator>>(std::istream &ist, Lot &l);

private:
    std::string mAddress;
    double mMinPrice;
    int mSize;
};

std::ostream& operator<<(std::ostream& ost, const Lot& l);

std::istream& operator>>(std::istream& ist, const Lot& l);

#endif //INC_030620_PART1_LOT_H
