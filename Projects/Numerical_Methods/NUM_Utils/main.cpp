
#include "NM_Utils.h"

int main() {
    MatDoub A(3,3);
    A[0][0] = 2.0;	A[0][1] = -1.0;	A[0][2] = 0.0;
    A[1][0] = -1.0;	A[1][1] = 2.0;	A[1][2] = -1.0;
    A[2][0] = 0.0;	A[2][1] = -1.0;	A[2][2] = 2.0;

    VecDoub b(3);
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;

    VecDoub x = nm_util::compCholesky(A, b);
    MatDoub C = nm_util::compCholeskyVariance(A, b);

    util::print(x, "solution x to Ax = b, obtained by LUd");
    util::print(C, "variance C");

    util::print(A*x, "A*x");
    util::print(b, "b");

    util::print(nm_util::vecSub(A*x, b), "A*x - b");





    return 0;
}

