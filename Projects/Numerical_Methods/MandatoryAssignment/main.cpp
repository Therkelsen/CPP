#include <iostream>
#include <iomanip>

#include <nr3.h>
#include <svd.h>
#include <ludcmp.h>
#include <qrdcmp.h>
#include <roots_multidim.h>
#include "utilities.h"

using namespace std;
using namespace util;

MatDoub loadData(const string& path){
    // This is a method for loading data from a file to a matrix.
    // File must have the following format for an M x N matrix:
    //      M
    //      N
    //    Row1
    //     .
    //     .
    //     .
    //    RowM

    ifstream inData;
    inData.open(path);

    if(!inData) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    int m, n;
    inData >> m >> n;
    MatDoub loadedData(m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(!inData.eof()) { // Only read data if not at the end of file
                inData >> loadedData[i][j];
            }
        }
    }

    inData.close();

    return loadedData;
}

bool vecEqual(VecDoub a, VecDoub b) {
    // Checks if two vectors are equal (didn't end up using this)
    if(a.size() != b.size()) {
        return false;
    }
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

VecDoub vecSub(VecDoub org, VecDoub sub){
    // Subtracts sub from org
    VecDoub subtractedVector;
    subtractedVector.assign(org.size(), 0);
    if(org.size() != sub.size()) {
        throw std::invalid_argument("VecDoubs must be of equal size!");
    } else {
        for(int i = 0; i < org.size(); i++) {
            subtractedVector[i] = org[i] - sub[i];
        }
    }
    return subtractedVector;
}

MatDoub matInverse(MatDoub v) {
    // Computes the inverse vector
    MatDoub v_inv(v.nrows(), v.ncols());
    if(v.nrows() != v.ncols()) {
        throw std::invalid_argument("MatDoub must be square! (n x n)");
    } else {
        v_inv.assign(v_inv.nrows(), v_inv.ncols(), 0);
        for (int i = 0; i < v.nrows(); i++) {
            for (int j = 0; j < v.ncols(); j++) {
                if(v[i][j] != 0) {
                    v_inv[i][j] = 1.0 / v[i][j];
                }
            }
        }
    }
    return v_inv;
}

double norm(const VecDoub& v) {
    // Computes the norm of v
    double sum = 0;

    for (int i = 0; i < v.size(); i++) {
        sum += pow(v[i], 2);
    }

    return sqrt(sum);
}

VecDoub normalize(const VecDoub& v) {
    // Normalizes v
    VecDoub normalized = v;
    double _norm = norm(normalized);
    for (int i = 0; i < normalized.size(); i++) {
        normalized[i] = normalized[i] / _norm;
    }
    return normalized;
}

VecDoub absolute(const VecDoub& v) {
    // Absolutes the elements of v
    VecDoub absolute = v;
    for (int i = 0; i < absolute.size(); i++) {
        absolute[i] = abs(absolute[i]);
    }
    return absolute;
}

struct Functions{
    // This struct is used for exercise 2
    Functions(double t) {_t = t;}

    void setT(double t) {_t = t;}

    double _t = 0;

    double a(double t) {return 1.1 * (1 + pow(t, 2));}
    double b(double t) {return 2.1 * (1 + 2 * pow(t, 2));}
    double c(double t) {return 0.8 * (1 + 3 * pow(t, 2));}
    double xe(double t) {return 2.3 * exp(-t);}
    double ye(double t) {return 4.8 * exp(-t);}
    double ze(double t) {return 0.7 * exp(-t);}

    VecDoub operator() (VecDoub input) {
        // input[0,1,2,3] is x, y, z, lambda

        VecDoub result(input.size());
        result[0] = input[0] - input[3] * a(_t) * (input[0] - xe(_t));
        result[1] = input[1] - input[3] * b(_t) * (input[1] - ye(_t));
        result[2] = input[2] - input[3] * c(_t) * (input[2] - ze(_t));
        result[3] = a(_t) * pow((input[0] - xe(_t)), 2) + b(_t) * pow((input[1] - ye(_t)), 2) + c(_t) * pow((input[0] - ze(_t)), 2) - 1;

        return result;
    }
};

double f(double x) {return cos(pow(x,3)) * exp(-x);}

VecDoub trapezoidalMethod(double (*f)(double x), int N, double a, double b, int iterations) {
    // This is an implementation of the trapezoidal method which runs for iteration times, doubling N for each iteration.
    VecDoub areas(iterations);
    areas.assign(iterations, 0);

    for(int i = 0; i < iterations; i++){
        double h = (b - a) / (N - 1);

        double area = 0;

        area += 0.5 * f(a);
        for (int j = 1; j < N - 1; j++) {
            area += f(a + h * j);
        }
        area += 0.5 * f(b);

        area *= h;
        areas[i] = abs(area);
        N *= 2;
    }

    return areas;
}

double richErrorEst(int alpha, int k, const VecDoub& areas, int i){
    // Estimates richardson error
    return abs((areas[i] - areas[i - 1])/(pow(alpha,k) - 1));
}

void Exercise5_print(int N, double a, double b, int iterations, VecDoub (*method)(double (*f)(double x), int N, double a, double b, int iterations)) {
    // Prints a nicely formatted table showing area, accuracy, richardson error, etc.
    cout << setw(5) << "i" << setw(10) << "N - 1" << setw(14) << "A(hi)" << setw(22) << "A(hi - 1) - A(hi)" << setw(17) << "Rich - alpha^k" <<  setw(16) << "Rich-error" << setw(16) << "F-Calculations" << endl;
    VecDoub areas = method(f, N, a, b, iterations);
    int fCalcs = 0, prevFCalcs = 0;
    double alphak, rich;
    for(int i = 0; i < areas.size(); i++) {
        fCalcs += N - 1 - prevFCalcs;
        switch (i) {
            case 0:
                cout << setw(5) << i + 1 << setw(10) << N - 1 << setw(14) << areas[i] << setw(22) << "*"                     << setw(17)
                << 4 << setw(16) << "*" << setw(12) << N << endl;
                break;
            case 1:
                cout << setw(5) << i + 1 << setw(10) << N - 1 << setw(14) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(17)
                << 4 << setw(16) << richErrorEst(2, 2, areas, i) << setw(12) << N << endl;
                break;
            case 2:
                cout << setw(5) << i + 1 << setw(10) << N - 1 << setw(14) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(17)
                << 4 << setw(16)  << richErrorEst(2, 2, areas, i)  << setw(12) << N << endl;
                break;
            default:
                cout << setw(5) << i + 1 << setw(10) << N - 1 << setw(14) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(17)
                << 4 << setw(16)  << richErrorEst(2, 2, areas, i)  << setw(12) << N << endl;
            break;

        }
        N *= 2;
        prevFCalcs = fCalcs;
    }
}

int main() {
    cout << defaultfloat << setprecision(7) << boolalpha;
    cout << "Data is loaded from the provided files Ex1A.dat and Ex1b.dat.\n" << endl;

    // Load the data provided in the two .dat files

    string path1 = "../Assets/Ex1A.dat";
    string path2 = "../Assets/Ex1b.dat";

    MatDoub A = loadData(path1);

    print(A, "A");

    MatDoub b  = loadData(path2);

    print(b, "b");

    cout << "========================================================================================================================" << endl;
    cout << "Exercise 1\n1.i\n" << endl;

    // Some inspiration is taken from Ole Wennerberg Nielsens examples uploaded to ItsLearning
    // This bit uses code from the svd.h header provided by Numerical Recipes
    // Computes the SVD elements of A

    SVD SVD(A);

    MatDoub U = SVD.u;
    MatDoub V = SVD.v;
    VecDoub W_diag = SVD.w;

    MatDoub W(W_diag.size(), W_diag.size());

    for(int i = 0; i < W.ncols(); i++) {
        for(int j = 0; j < W.nrows(); j++) {
            if(i == j) {
                W[i][j] = W_diag[i];
            } else {
                W[i][j] = 0;
            }
        }
    }

    cout << "A = U*W*T(V):" << endl;

    print(A, "A");
    print(U, "U");
    print(W, "W");
    print(T(V), "T(V)");

    cout << "\n1.ii\n" << endl;

    // Computes the inverse of W
    MatDoub W_inv = matInverse(W);

    // Turns b into a VecDoub
    VecDoub b_vec(b.nrows());

    for (int i = 0; i < b.nrows(); i++) {
        b_vec[i] = b[0][i];
    }

    print(W_inv, "W Inverse");

    VecDoub x(A.ncols());

    // Manually computes the x solution to Ax = b that minimizes ||Ax-b||

    x = V * W_inv * T(U) * b_vec;

    cout << endl;
    print(x, "x");
    cout << endl;

    cout << endl;
    print(A*x, "A*x");
    cout << endl;

    cout << endl;
    print(b_vec, "b");
    cout << endl;

    VecDoub Ax = A*x;

    // Computes the random fitting

    double randfit = sqrt(((A.nrows()*1.0)-(A.ncols()*1.0))/(A.nrows()*1.0));

    cout << "Random fitting " << randfit << endl;

    // Computes the epsilon residual for the first solution

    double e_residual_x = norm(vecSub(Ax, b_vec))/norm(b_vec);

    cout << "x Residual " << e_residual_x << endl;

    // Compares residual to random fitting

    cout << "x Compared to random fitting " << e_residual_x - randfit << endl;

    VecDoub x2(A.ncols());

    // Uses the svd header to compute the x solution to Ax = b that minimizes ||Ax-b||

    SVD.solve(b_vec,x2,SVD.eps);

    VecDoub Ax2 = A*x2;

    cout << endl;
    cout << endl;
    print(x2, "x2");
    cout << endl;

    cout << endl;
    print(A*x2, "A*x2");
    cout << endl;

    cout << endl;
    print(b_vec, "b");
    cout << endl;

    // Computes the epsilon residual for the second solution

    double e_residual_x2 = norm(vecSub(Ax2, b_vec))/norm(b_vec);

    cout << "Random fitting " << randfit << endl;

    cout << "x2 Residual " << e_residual_x2 << endl;

    // Compares residual to random fitting

    cout << "x2 Compared to random fitting " << e_residual_x2 - randfit << "\n" << endl;

    print(vecSub(Ax, Ax2), "Ax - Ax2");

    cout << "\nDifference in comparison: " << (e_residual_x - randfit) - (e_residual_x2 - randfit) << endl;

    cout << "========================================================================================================================" << endl;
    cout << "Exercise 2\n2.i\n" << endl;

    double t = 1.2;

    Functions f2(t);

    bool check = false;

    VecDoub roots_1(4);

    roots_1.assign(roots_1.size(), 0);

    // Uses newtons method to find roots for the four functions, for t = 1.2
    newt(roots_1, check, f2);

    cout << "Did newt find usable roots? " << !check << endl;

    print(roots_1, "Roots for t = 1.2");

    // Computes d
    cout << "d = " << sqrt(pow(roots_1[0], 2) + pow(roots_1[1], 2) + pow(roots_1[2], 2)) << endl;

    cout << "\n2.ii\n" << endl;

    t = 1.4;

    f2.setT(t);

    check = false;

    VecDoub roots_2(4);

    roots_2.assign(roots_2.size(), 0);

    // Uses newtons method to find roots for the four functions, for t = 1.2
    newt(roots_2, check, f2);

    cout << "Did newt find usable roots? " << !check << endl;

    print(roots_2, "Roots for t = 1.4");

    // Computes d
    cout << "d = " << sqrt(pow(roots_2[0], 2) + pow(roots_2[1], 2) + pow(roots_2[2], 2)) << endl;

    cout << "========================================================================================================================" << endl;
    cout << "Exercise 5\nii\n" << endl;

    int N = 2;
    int a = 1;
    int b2 = 3;
    int iterations = 7;

    // Uses trapezoidal method to approximate the area for a given N
    VecDoub ex5area = trapezoidalMethod(f, N, a, b2, iterations);

    cout << endl;

    Exercise5_print(N, a, b2, iterations, trapezoidalMethod);

    return 0;
}
