#include <iostream>
#include <iomanip>

#include <nr3.h>
#include <svd.h>
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(!inData.eof()) { // Only read data if not at the end of file
                inData >> loadedData[j][i];
            }
        }
    }

    inData.close();

    return loadedData;
}

double f1(double x) {
    return x - cos(x);
}

double df1d(double x) {
    return 1 + sin(x);
}

double f5(double x) {
    return cos(pow(x,3)) * exp(-x);
}

VecDoub newtonsMethod(double (*f)(double x), double (*dfd)(double x),int iterations = 1) {
    VecDoub x(iterations + 1);
    x[0] = 0;
    for (int i = 0; i < iterations; i++) {
        x[i + 1] = x[i] - f(x[i])/dfd(x[i]);
    }
    return x;
}

VecDoub trapezoidalMethod(double (*f)(double x), int N, double a, double b, int iterations) {
    VecDoub areas(iterations);

    for(int i = 0; i < iterations; i++){
        double h = (b - a) / (N - 1);

        double area = 0;

        area += 0.5 * f(a);
        for (int j = 1; j < N - 2; j++) {
            area += f(a + h * j);
        }
        area += 0.5 * f(b);

        area *= h;
        areas[i] = area;
        N *= 2;
    }

    return areas;
}

double richardsonErrorEstimation(int alpha, int k, const VecDoub& areas){
    return (areas[areas.size()] - areas[areas.size() - 1])/(pow(alpha,k) - 1);
}

int main() {
    cout << fixed << setprecision(7);
    cout << "Data is loaded from the provided files Ex1A.dat and Ex1b.dat.\n" << endl;

    string path1 = "../Assets/Ex1A.dat";
    string path2 = "../Assets/Ex1b.dat";

    MatDoub A = loadData(path1);

    print(A, "A");

    MatDoub b  = loadData(path2);

    print(b, "b");

    cout << "Exercise 1\n"
            "i) (10 points) Find the Singular Value Decomposition (SVD) A = U*W*T(V).\n"
            "State the diagonal elements in W. Submit the used code.\n" << endl;
    // Some inspiration is taken from Oles examples uploaded to ItsLearning
    SVD SVD(A);
    VecDoub x(A.ncols());
    VecDoub x_2(A.ncols());

    MatDoub U = SVD.u;
    MatDoub V = SVD.v;
    VecDoub W = SVD.w;

    print(W, "W");

    cout << "ii) (5 points) Use SVD to compute the solution x to Ax = b.\n"
            "State the solution x. Submit the used code.\n" << endl;

    MatDoub W_inv = MatDoub(W.size(),W.size());
    for(int i = 0; i< W.size(); i++) {
        W_inv[i][i] = 1.0 / W[i];
    }

    VecDoub b_vec(b.nrows());

    for (int i = 0; i < b.nrows(); i++) {
        b_vec[i] = b[0][i];
    }

    //cout << "y:" << endl;
    //print(y);

    x = V * W_inv * T(U) * b_vec;

    print(x);

    print(A*x, "A*x");

    cout << "iii) (5 points) State a vector y element of R^10 so that \174\174y\174\174 = 1 and y * (Ax) is approximately 0 for any vector x with \174\174x\174\174 = 1.\n" << endl;

    cout << "\nExercise 2\n"
            "i) (6 points) At time t = 1:2, find a solution (x; y; z; lambda) satisfying the firstrst order conditions in Eq.(1).\n"
            "Use Newtons method starting with (x; y; z; lambda) = (0; 0; 0; 0) and with a required tolerance of 10^8.\n"
            "State your result for x; y; z and compute and state the distance to the origin d = sqrt(x^2 + y^2 + z^2).\n"
            "Submit the used code. As a check that you programmed everything correct, d should be approximately 1.22.\n"
            "As d > 1, the two objects are not penetrating each other." << endl;

    cout << "\nExercise 5\n"
            "i) (5 points) For N = 2, state an analytical expression for the approximation of the integral as obtained by the Trapezoidal method.\n"
            "\nFrom lecture 8, the formula for the trapezoidal method is given by\n"
            "h*[1/2 * f0 + f1 + f2 + ... + fN-2 + 1/2 * fN-1]\n"
            "where h = (b - a)/(N)\n" << endl;

    cout << "ii) (10 points) With N = 2; 4; 8; ... use the Trapezoidal method to approximate the integral.\n"
            "Terminate the subdivisions when you reach a proven accuracy of better than 10^5.\n" << endl;

    VecDoub ex5area = trapezoidalMethod(f5, 2, 1, 3, 20);

    print(ex5area, "ex5area");

    cout << "\nError estimated: " << richardsonErrorEstimation(2, 2, ex5area);
    return 0;
}
