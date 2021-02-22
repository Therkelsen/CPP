//
// Created by Thomas Therkelsen on 15-02-2021.
//

#ifndef INC_5_1_PI_H
#define INC_5_1_PI_H
#include <cmath>

class Pi {
private:

public:
    Pi();
    double pi = M_PI;
    double piApproximated;
    double approximatePi(int n);

    double approximatePiOptimal(int n);
};


#endif //INC_5_1_PI_H
