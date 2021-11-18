//
// Created by Thomas Therkelsen on 28-05-2021.
//

#include "Ticket.h"

Ticket::Ticket() {

}

int Ticket::getMTheater() const {
    return mTheater;
}

void Ticket::setMTheater(int mTheater) {
    Ticket::mTheater = mTheater;
}

int Ticket::getMTicketNo() const {
    return mTicketNo;
}

void Ticket::setMTicketNo(int mTicketNo) {
    Ticket::mTicketNo = mTicketNo;
}

double Ticket::getMPrice() const {
    return mPrice;
}

void Ticket::setMPrice(double mPrice) {
    Ticket::mPrice = mPrice;
}

const char *Ticket::getMDate() const {
    return mDate;
}

const char *Ticket::getMTime() const {
    return mTime;
}

char *Ticket::getMSeat() const {
    return mSeat;
}

void Ticket::setMSeat(char *mSeat) {
    Ticket::mSeat = mSeat;
}

char *Ticket::getMMovie() const {
    return mMovie;
}

void Ticket::setMMovie(char *mMovie) {
    Ticket::mMovie = mMovie;
}

bool Ticket::isM3D() const {
    return m3D;
}

void Ticket::setM3D(bool m3D) {
    Ticket::m3D = m3D;
}