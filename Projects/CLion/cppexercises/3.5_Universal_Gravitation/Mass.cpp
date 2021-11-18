//
// Created by Thomas Therkelsen on 01-03-2021.
//

#include "Mass.h"
#include <cmath>

double Mass::getMass() const{
    return mass;
}

double Mass::gravitation(Mass m, double distance){
    return G*((getMass()*m.getMass())/(pow(distance, 2))); // F = G * (m1 * m2) / r^2
}

