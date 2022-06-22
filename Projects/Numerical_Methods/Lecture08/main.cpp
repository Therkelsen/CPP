#include <iostream>
#include <iomanip>
#include <cmath>
#include <nr3.h>
#include <quadrature.h>
#include <derule.h>
#include <utilities.h>

#include <stdlib.h>

using namespace std;

double f1(double x) {
    return cos(pow(x, 2)) * exp(-x);
}

double f2(double x) {
    return sqrt(x) * cos(pow(x, 2)) * exp(-x);
}

double f3(double x) {
    return 1 / sqrt(x) * cos(pow(x, 2)) * exp(-x);
}

double f4(double x) {
    return 1000 * exp(-1 / x) * exp(-1 / (1 - x));
}

double f5(double x, double tau) {
    return cos(pow(x,2))*exp(-x);
}

double f6(double x, double tau) {
    if( x < 0.0001 ) {
        return (1/sqrt(tau))*cos(pow(x,2))*exp(-x);
    }
    return (1.0/sqrt(x)) * cos(pow(x,2))*exp(-x);
}

double f7(double x, double tau) {
    return 1000*exp(-1.0/x)* exp(-1.0/(1.0-x));
}

double f8(double x) {
    return 1000 * exp(-1.0/x) * exp(-1.0/(1.0 - x));
}

double f9(double x) {
    return (1.0 / sqrt(x)) * cos(pow(x, 2)) * exp(-x);
}

template<class T>
VecDoub trapezoidalMethod(T &f, const VecDoub& info) {
    // Uses the trapezoidal method to approximate the numerical integration of a given function

    int N = info[0]; // Number of initial subdivisions
    int maxIt = info[1]; // Number of iterations
    double a = info[2]; // lower bound
    double b = info[3]; // upper bound
    int acc = info[4]; // desired accuracy

    cout << scientific << "Attempting numerical integration by Trapezoidal method at accuracy of " << abs(1 * pow(10, (-acc))) << endl;

    VecDoub areas, areas2;
    areas.assign(maxIt, 0);

    for(int i = 0; i < maxIt; i++) {
        double h = (b - a) / (N - 1);

        double area = 0;
        area += 0.5 * f(a) + 0.5 * f(b);
        for (int j = 1; j < N - 1; j++) {
            area += f(a + h * j);
        }

        area *= h;
        areas[i] = abs(area);
        N *= 2;

        if(i > 0) {
            if(abs(areas[i-1]-areas[i]) < abs(pow(10, (-acc)))) {
                cout << "Success: Reached accuracy of " << abs(pow(10, (-acc))) << ", terminating."<< endl;
                areas2.assign(i, 0);
                break;
            } else if (i == maxIt - 1) {
                cout << "Error: Exceeded maximum amount of iterations before reaching accuracy, terminating." << endl;
                areas2.assign(i, 0);
                break;
            }
        }
    }

    for(int i = 0; i < areas2.size(); i++) {
        areas2[i] = areas[i];
    }
    return areas2;
}

template<class T>
VecDoub extendedMidpointMethod(T &f, const VecDoub& info) {
    // Uses the extended method to approximate the numerical integration of a given function
    int N = info[0]; // Number of initial subdivisions
    int maxIt = info[1]; // Number of iterations
    double a = info[2]; // lower bound
    double b = info[3]; // upper bound
    int acc = info[4]; // desired accuracy

    cout << scientific << "Attempting numerical integration by Extended Midpoint method at accuracy of " << abs(1 * pow(10, (-acc))) << endl;

    VecDoub areas, areas2;
    areas.assign(maxIt, 0);

    for(int i = 0; i < maxIt; i++){
        double h = (b - a) / (N - 1);

        double area = 0;

        for (int j = 0; j < N - 1; j++) {
            area += f(a + h * j + h * 0.5);
        }

        area *= h;
        areas[i] = area;
        N *= 2;

        if(i > 0) {
            if(abs(areas[i-1]-areas[i]) < abs(pow(10, (-acc)))) {
                cout << "Success: Reached accuracy of " << abs(pow(10, (-acc))) << ", terminating."<< endl;
                areas2.assign(i, 0);
                break;
            } else if (i == maxIt - 1) {
                cout << "Error: Exceeded maximum amount of iterations before reaching accuracy, terminating." << endl;
                areas2.assign(i, 0);
                break;
            }
        }
    }

    for(int i = 0; i < areas2.size(); i++) {
        areas2[i] = areas[i];
    }
    return areas2;
}

template<class T>
VecDoub simpsonsMethod(T &f, const VecDoub& info) {
    // Uses simpsons method to approximate the numerical integration of a given function
    int N = info[0]; // Number of initial subdivisions
    int maxIt = info[1]; // Number of iterations
    double a = info[2]; // lower bound
    double b = info[3]; // upper bound
    int acc = info[4]; // desired accuracy

    cout << scientific << "Attempting numerical integration by Simpsons method at accuracy of " << abs(1 * pow(10, (-acc))) << endl;

    VecDoub areas, areas2;
    areas.assign(maxIt, 0);

    for(int i = 0; i < maxIt; i++) {
        double h = (b - a) / (N - 1);

        double area = 1./3 * f(a) + 1./3 * f(b);
        for (int j = 1; j < N - 1; j++) {
            if(j % 2 != 0) {
                area += 4./3 * f(a + h * j);
            } else {
                area += 2./3 * f(a + h * j);
            }
        }
        areas[i] = area * h;
        N *= 2;

        if(i > 0) {
            if(abs(areas[i-1]-areas[i]) < abs(pow(10, (-acc)))) {
                cout << "Success: Reached accuracy of " << abs(pow(10, (-acc))) << ", terminating."<< endl;
                areas2.assign(i, 0);
                break;
            } else if (i == maxIt - 1) {
                cout << "Error: Exceeded maximum amount of iterations before reaching accuracy, terminating." << endl;
                areas2.assign(i, 0);
                break;
            }
        }
    }

    for(int i = 0; i < areas2.size(); i++) {
        areas2[i] = areas[i];
    }
    return areas2;
}

template<class T>
double derule(T &func, const double a, const double b, const double acc) {
    //VecDoub areas;

    Doub count = 0;
    Doub N = 0;
    Doub Ah0 = 0;
    Doub Ah1 = 0;
    DErule<T> rule(func, a, b, 4.3); //3.7    4.3  Vælges ud fra sværheden af singulariteten ved 1/sqrt(x) er 4.3 passende
    while((abs(Ah0-Ah1)/Ah0 > abs(1 * pow(10, (-acc))) || count==0)) {
        count++;
        N = pow(2,count);
        Ah1=Ah0;
        Ah0 = rule.next();
        cout << count << "  " << Ah0 << "   " << abs(Ah0-Ah1) << endl;
        //areas[count] = Ah0;
    }
    return Ah0;
}

double richErrorEst(double alphak, const VecDoub& areas, int i){
    // Estimates richardson error
    return abs((areas[i] - areas[i - 1])/(alphak - 1));
}

double richAlphak(const VecDoub& areas, int i) {
    // Estimates alpha^k
    return abs(areas[i - 2] - areas[i - 1])/abs(areas[i - 1] - areas[i]);
}

void numIntPrint(const VecDoub& areas, const VecDoub& info, const std::string& method) {
    // Prints a nicely formatted table showing area, accuracy, richardson error, etc.
    int N = info[0];
    int maxIt = info[1];
    double a = info[2];
    double b = info[3];
    int acc = info[4];

    cout << setprecision(acc - 4) << left << setw(7) << "i" << setw(22) << "A(hi)" << setw(22) << "A(hi - 1) - A(hi)" << setw(22) << "Rich - alpha^k" <<  setw(22) << "Rich-error" << setw(16) << "F-Calculations" << endl;
    int fCalcs, prevFCalcs = 0;
    for(int i = 0; i < areas.size(); i++) {
        fCalcs += N - prevFCalcs;
        switch (i) {
            case 0:
                cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << "*" << setw(22)
                     << "*" << setw(22) << "*" << setw(16) << fCalcs << endl;
                break;
            case 1:
                cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(22)
                     << "*" << setw(22) << richErrorEst(richAlphak(areas, i), areas, i) << setw(16) << fCalcs << endl;
                break;
            case 2:
                cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(22)
                     << "*" << setw(22)  << richErrorEst(richAlphak(areas, i), areas, i)  << setw(16) << fCalcs << endl;
                break;
            default:
                cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(22)
                     << richAlphak(areas, i) << setw(22)  << richErrorEst(richAlphak(areas, i), areas, i)  << setw(16) << fCalcs << endl;
                break;
        }
        N *= 2;
        prevFCalcs = fCalcs;
    }
}

int main() {
    cout << boolalpha << endl;

    VecDoub info(5);
    info.assign(5,0);

    int N = 2; info[0] = N;
    int maxIt = 21; info[1] = maxIt;
    int a = 0; info[2] = a;
    int b = 1; info[3] = b;
    int acc = 10; info[4] = acc;

    VecDoub areas = trapezoidalMethod(f1, info);
    numIntPrint(areas, info, "Trapezoidal");

    cout << endl;

    areas = extendedMidpointMethod(f1, info);
    numIntPrint(areas, info, "Extended Midpoint");

    cout << endl;

    areas = simpsonsMethod(f1, info);
    numIntPrint(areas, info, "Simpsons");

    //derule(f5, a, b, acc);

    return 0;
}
