
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

int main() {
    cout << boolalpha;

    MatDoub A(3,3);
    A[0][0] = 2.0;	A[0][1] = -1.0;	A[0][2] = 1.0;
    A[1][0] = -1.0;	A[1][1] = 2.0;	A[1][2] = -1.0;
    A[2][0] = 0.0;	A[2][1] = -1.0;	A[2][2] = 2.0;

    VecDoub b(3);
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;

    VecDoub x = nm_util::compCholesky(A, b);

    nm_util::trapezoidalMethod(f1, )

//    MatDoub C = nm_util::compLUDVariance(A, b);

//    util::print(A*x, "A*x");
//    util::print(b, "b");
//
//    util::print(nm_util::vecSub(A*x, b), "A*x - b");

    return 0;
}

