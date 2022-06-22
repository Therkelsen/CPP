
#include "NM_Utils.h"

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

int main() {
    cout << boolalpha;

//    MatDoub A(3,3);
//    A[0][0] = 2.0;	A[0][1] = -1.0;	A[0][2] = 1.0;
//    A[1][0] = -1.0;	A[1][1] = 2.0;	A[1][2] = -1.0;
//    A[2][0] = 0.0;	A[2][1] = -1.0;	A[2][2] = 2.0;
//
//    VecDoub b(3);
//    b[0] = 1;
//    b[1] = 2;
//    b[2] = 3;
//
//    VecDoub x = nm_util::compCholesky(A, b);

    VecDoub info(5);
    info.assign(5,0);

    int N = 2; info[0] = N;
    int maxIt = 21; info[1] = maxIt;
    int a = 0; info[2] = a;
    int b = 1; info[3] = b;
    int acc = 10; info[4] = acc;

    VecDoub areas = nm_util::numIntTrapezoidalMethod(f1, info);
    nm_util::numIntPrint(areas, info, "Trapezoidal");

    cout << endl;

    areas = nm_util::numIntExtendedMidpointMethod(f1, info);
    nm_util::numIntPrint(areas, info, "Extended Midpoint");

    cout << endl;

    areas = nm_util::numIntSimpsonsMethod(f1, info);
    nm_util::numIntPrint(areas, info, "Simpsons");

    //derule(f5, a, b, acc);

    return 0;
}

