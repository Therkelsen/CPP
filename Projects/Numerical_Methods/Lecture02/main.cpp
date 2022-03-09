#include <iostream>
#include <iomanip>
#include <fstream>
#include "../../Assets/NR_C301/code/nr3.h"
#include "../../Assets/NR_C301/code/ludcmp.h"
#include "../../Assets/NR_C301/code/cholesky.h"
#include <math.h>
#include "../../Assets/NR_C301/code/svd.h"
#include <string>
#include <exception>
#include "../../Assets/NR_C301/code/utilities.h"

using namespace std;

int main() {
    /*
     *  Pontius
     */
    VecDoub xPont(40); VecDoub yPont(40);
    ifstream Pont("C:\\Users\\Thomas Therkelsen\\Documents\\GitHub\\Numerical_Methods\\Assets\\PontiusData.dat");
    for(int i = 0; i < 40; i++) {
        Pont >> yPont[i];
        Pont >> xPont[i];
    }

    /*for(int i = 0; i < xPont.size(); i++) {
        cout << left << setw(0);
        cout << "xPont[" << i << "] = " << xPont[i];
        cout << right << setw(25) << setprecision(5);
        cout << " yPont[" << i << "] = " << yPont[i] << endl;
    }*/

    MatDoub A(40,3);
    for(int i=0; i <A.nrows();i++ )
    {
        A[i][0]=1.0; A[i][1]= xPont[i]; A[i][2]= xPont[i] * xPont[i];
    }

    MatDoub AT = util::Transpose(A);

    // At * A * x = At * y
    MatDoub ATA = AT*A;
    VecDoub ATy = AT*yPont;

    LUdcmp LU(ATA);
    VecDoub x(3);
    MatDoub C;
    LU.solve(ATy,x);

    util::print(x,"Pontius solution using LU:");
    LU.inverse(C);
    util::printDiag(C,"Variance:");
    cout << endl;


    Cholesky Cho (ATA);
    Cho.solve(ATy,x);
    util::print(x,"Pontius solution using Cholesky:");

    Cho.inverse(C);
    util::printDiag(C,"Variance:");
    cout << endl << endl;
    /*
     * Cholesky
     */

    VecDoub xFilip(82); VecDoub yFilip(82);
    ifstream Filip("C:\\Users\\Thomas Therkelsen\\Documents\\GitHub\\Numerical_Methods\\Assets\\FilipData.dat");
    for(int i = 0; i < 82; i++) {
        Filip >> yFilip[i];
        Filip >> xFilip[i];
    }

    MatDoub A2(xFilip.size(),11);
    for(int i=0; i <A2.nrows();i++ )
    {
        for(int j = 0; j < A2.ncols(); j++)
            A2[i][j]= pow(xFilip[i],(double) j);
    }

    MatDoub AT2 = util::Transpose(A2);

    // At * A * x = At * y
    MatDoub ATA2 = AT2*A2;
    VecDoub ATy2 = AT2*yFilip;

    VecDoub x2(A2.ncols());
    LUdcmp LUFilip (ATA2);
    LUFilip.solve(ATy2, x2);
    util::print(x2, "Filip using LU:");
    LUFilip.inverse(C);
    util::printDiag(C, "Variance:");
    cout << endl;

    cout << "Filip solution using Cholesky:" << endl;
    try {
        Cholesky CholeskyFilip (ATA2);
    }
        //catch (NRerror &e) { NRcatch(e); }

    catch (...) {std::cout << "Cholesky could not be computed" << endl; exit(1); }

    return 0;
}
