
#include "../../Assets/NR_C301/code/nr3.h"
#include "../../Assets/NR_C301/code/ludcmp.h"

#include "../../Assets/NR_C301/code/utilities.h"

using namespace std;
using namespace util;

// Exercise 1
// Solving A x = b using LU decomposition
int main() {

    MatDoub A(3,3);
    A[0][0] = 1.0;	A[0][1] = 2.0;	A[0][2] = 3.0;
    A[1][0] = 2.0;	A[1][1] = -4.0;	A[1][2] = 6.0;
    A[2][0] = 3.0;	A[2][1] = -9.0;	A[2][2] = -3.0;

    VecDoub b(3);
    b[0] = 5.0;
    b[1] = 18.0;
    b[2] = 6.0;

    VecDoub x(3);
    LUdcmp LU(A);

    auto L = LU.lu;
    L[0][1] = L[0][2] = L[1][2] = 0;
    L[0][0] = L[1][1] = L[2][2] = 1;
    print(L, "L");

    auto U = LU.lu;
    U[1][0] = U[2][0] = U[2][1] = 0;
    print(U, "U");

    LU.solve(b,x);

    print(A,"A");
    print(L*U,"L*U");
    print(L*U*x,"L*U*x");
    print(x,"x");

    return 0;
}
