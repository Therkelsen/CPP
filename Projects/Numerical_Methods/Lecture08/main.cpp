#include <iostream>
#include <iomanip>
#include <cmath>

#include <Eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

double f1(double x) {
    return cos(pow(x, 2)) * exp(-x);
    // return sqrt(x) * cos(pow(x, 2)) * exp(-x);
    // return 1 / sqrt(x) * cos(pow(x, 2)) * exp(-x);
    // return 1000 * exp(-1 / x) * exp(-1 / (1 - x));
}

VectorXd extendedMidpointMethod(double (*f)(double x), int N, double a, double b, int iterations) {
    VectorXd areas;
    areas.resize(iterations);

    for(int i = 0; i < iterations; i++){
        double h = (b - a) / (N - 1);

        double area = 0;

        for (int j = 0; j < N - 1; j++) {
            area += f(a + h * j + h * 0.5);
        }

        area *= h;
        areas(i) = area;
        N *= 2;
    }

    return areas;
}

void print(int N, double a, double b, int iterations, double accArea, VectorXd (*method)(double (*f)(double x), int N, double a, double b, int iterations)) {
    cout << setw(5) << "i" << setw(12) << "A(hi)" << setw(20) << "A(hi - 1) - A(hi)" << setw(17) << "Rich - alpha^k" << setw(12) << "A(hi) - A" << setw(12) << "Rich-error" << setw(12) << "Amount of f-calculations" << endl;
    VectorXd areas = method(f1, N, a, b, iterations);
    for(int i = 0; i < areas.size(); i++) {
        switch (i) {
            case 0:
                cout << setw(5) << i + 1 << setw(12) << areas(i) << setw(20) << "*"  << setw(17) << "*" << setw(12) << areas(i)-accArea << setw(12) << "*" << setw(12) << "" << endl;
                break;
            case 1:
                cout << setw(5) << i + 1 << setw(12) << areas(i) << setw(20) << areas(i - 1) - areas(i) << setw(17) << "*" << setw(12) << areas(i)-accArea << setw(12) << "*" << setw(12) << "" << endl;
                break;
            case 2:
                cout << setw(5) << i + 1 << setw(12) << areas(i) << setw(20) << areas(i - 1) - areas(i) << setw(17) << "" << setw(12) << areas(i)-accArea << setw(12) << "" << setw(12) << "" << endl;
                break;
            default:
                cout << setw(5) << i + 1 << setw(12) << areas(i) << setw(20) << areas(i - 1) - areas(i) << setw(17) << "" << setw(12) << areas(i)-accArea << setw(12) << "" << setw(12) << "" << endl;
            break;

        }

    }
}

int main() {
    cout << fixed << setprecision(7) << left;

    int N = 5;
    int a = 0;
    int b = 1;
    int iterations = 10;

    cout << "\nExtended Midpoint Method (N = " << N << " , a = " << a << " , b = " << b << "):" << endl;
    print(N, a, b, iterations, 0.590051, extendedMidpointMethod);

    return 0;
}
