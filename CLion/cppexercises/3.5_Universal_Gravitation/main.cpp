
#include <iostream>
#include "Mass.h"
#include <iostream>
#include <cmath>
using namespace std;

int main() {

    Mass earth(5.9722*pow(10, 24));
    Mass moon(7.3476*pow(10, 22));

    cout << "Mass of the Earth is: " << earth.getMass() << endl;
    cout << "Mass of the Moon is:  " << moon.getMass() << endl;

    cout << "The Earths gravitational force on the Moon: " << earth.gravitation(moon, 384400) << endl;
    cout << "The Moons gravitational force on the Earth: " << moon.gravitation(moon, 384400)  << endl;

    return 0;
}
