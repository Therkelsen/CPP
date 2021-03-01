//
// Created by Thomas Therkelsen on 01-03-2021.
//

#ifndef INC_3_5_UNIVERSAL_GRAVITATION_MASS_H
#define INC_3_5_UNIVERSAL_GRAVITATION_MASS_H
#include <cmath>

class Mass {
private:
    double mass;
    const double G {6.674*pow(10.0,-11.0)}; // 6.674 * 10^-11

public:
    Mass(double mass){
        this->mass = mass;
    }

    double getMass() const;

    double gravitation(Mass m, double distance);
};

#endif //INC_3_5_UNIVERSAL_GRAVITATION_MASS_H
