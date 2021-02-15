//
// Created by Thomas Therkelsen on 15-02-2021.
//

#include "Pi.h"

Pi::Pi() = default;

double Pi::approximatePi(int n) {
    double approx {1};
    for (int i = 0; i <= n; i++) {
        double den = (i*2 + 3);
        double frac = (double)1/den;
        i % 2 == 0 ? (approx -= frac) : (approx += frac);
    }
    piApproximated = 4*approx;
    return piApproximated;
}