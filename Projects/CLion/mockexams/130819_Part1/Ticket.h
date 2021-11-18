//
// Created by Thomas Therkelsen on 28-05-2021.
//

#ifndef INC_130819_PART1_TICKET_H
#define INC_130819_PART1_TICKET_H

class Ticket {
public:
    Ticket();

    int getMTheater() const;

    void setMTheater(int mTheater);

    int getMTicketNo() const;

    void setMTicketNo(int mTicketNo);

    double getMPrice() const;

    void setMPrice(double mPrice);

    const char *getMDate() const;

    const char *getMTime() const;

    char *getMSeat() const;

    void setMSeat(char *mSeat);

    char *getMMovie() const;

    void setMMovie(char *mMovie);

    bool isM3D() const;

    void setM3D(bool m3D);

private:
    int mTheater;
    int mTicketNo;
    double mPrice;
    char mDate[11];
    char mTime[6];
    char* mSeat;
    char* mMovie;
    bool m3D;
};

#endif //INC_130819_PART1_TICKET_H
