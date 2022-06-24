
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

double dxt(double const &x, double const &y) {
    return x*y;
}

double dyt(double const &x) {
    return -pow(x, 2);
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
    int b = 5; info[3] = b;
    int acc = 10; info[4] = acc;
//
//    VecDoub areas = nm_util::numIntTrapezoidalMethod(f1, info);
//    nm_util::numIntPrint(areas, info, "Trapezoidal");
//
//    cout << endl;
//
//    areas = nm_util::numIntExtendedMidpointMethod(f1, info);
//    nm_util::numIntPrint(areas, info, "Extended Midpoint");
//
//    cout << endl;
//
//    areas = nm_util::numIntSimpsonsMethod(f1, info);
//    nm_util::numIntPrint(areas, info, "Simpsons");

    //derule(f5, a, b, acc);

//    Doub s , olds = 0.0 , oldolds =0.0,rn=0.0, r=0.0, oldr = 0.0,oldoldr=0.0 ;
//    cout << setw(15) << "hinv" <<	setw(15) << "Sn" << setw(15) << "k1" << setw(15) << "Rn" << setw(15) << "k2" <<  setw(15) << "R2n" << endl;
//    for(int j=0;j<15;j++){
//
//        s = nm_util::Euler(1,1,0,5,5*pow(2,j));  // 1(1) and 2(3)
//        //s = Leap_Frog(1,1,0,10,5*pow(2,j));//1(1) and 2(3)
//
//        //s =Midpoint(1,1,0,5,5*pow(2,j)); // 2(3) and 3(8)
//
//        //s=Trapezoidal(1,1,0,5,5*pow(2,j));// 2(3) and 3(8)
//
//        //s = CalcRK4(1,1,0,5,5*pow(2,j)); //4(15) and 5(24)
//
//        cout << setw(15) << 5*pow(2,j);
//        cout << setw(15) << s;
//        if (oldolds != 0.0){ cout << setw(15) << log2(abs((oldolds-olds)/(olds-s)));}
//        else {cout << setw(15) << " ";}
//        if (olds != 0.0){ r=s+(s-olds)/1.0;cout << setw(15) << r;} // We see that k1 tends towards 2,and with alpha=2 we get alpha^k-1 = 3
//        else {cout << setw(15) << " ";}
//        if (oldoldr != 0.0){ cout << setw(15) << log2(abs((oldoldr-oldr)/(oldr-r)));}
//        else {cout << setw(15) << " ";}
//        if (oldr != 0.0){ rn=r+(r-oldr)/3.0;cout << setw(15) << rn;} // We see that k2 tends towards 4,and with alpha=2 we get alpha^k-1 = 15
//        else {cout << setw(15) << " ";}
//        cout << endl;
//
//
//        oldoldr =oldr;
//        oldolds=olds;
//        oldr=r;
//        olds=s;
//    }

    VecDoub area = nm_util::IVPEuler(dxt, dyt, 1.0, 1.0, a, b, N, maxIt);
    nm_util::numIntPrint(area, info);

    return 0;
}
