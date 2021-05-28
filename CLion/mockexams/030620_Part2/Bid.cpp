//
// Created by Thomas Therkelsen on 28-05-2021.
//

#include "Bid.h"

bool Bid::operator<(const Bid &rhs) {
    return rhs.mPrice > mPrice;
}
