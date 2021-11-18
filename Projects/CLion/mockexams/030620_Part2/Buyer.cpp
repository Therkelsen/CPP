//
// Created by Thomas Therkelsen on 28-05-2021.
//

#include "Buyer.h"

void Buyer::addBid(Plot *plot, double price, int priority) {
    Bid *b;
    b->setPlot(plot);
    b->setPrice(price);
    b->setPriority(priority);
    mBids.push_back(b);
}
