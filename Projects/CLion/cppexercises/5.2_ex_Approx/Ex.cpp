//
// Created by Thomas Therkelsen on 15-02-2021.
//

#include "Ex.h"
#include <cmath>

Ex::Ex()= default;

long long Ex::factorial(int n){
    long long fact {1};
    for (int i = 1; i <= n; i++) {
        fact = fact*i;
    }
    return fact;
}

long long Ex::approxEx(int x, int n){
    double approx = (1 + x);
    for (int i = 0; i < n; i++) {
        double den = (double)(factorial(1 + i));
        double frac = (1/den)*pow(x, (1 + i));
        approx += frac;
    }
    return (long long) approx;
}

/*double Pi::approximatePi(int n) {
    double approx {1};
    for (int i = 0; i <= n; i++) {
        double den = (i*2 + 3);
        double frac = (double)1/den;
        i % 2 == 0 ? (approx -= frac) : (approx += frac);
    }
    piApproximated = 4*approx;
    return piApproximated;
}*/