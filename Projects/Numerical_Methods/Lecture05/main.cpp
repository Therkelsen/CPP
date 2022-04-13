#include <iostream>
#include <iomanip>
#include <cmath>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

/*
Consider the simple problem
f(x)=x-cos(x)=0
where there must be a solution X between 0 and Pi/2.Implement Newton, Secant, Bisection, Regula Falsiand Ridder for this problem.
Each method produces a sequence x_0, x_1, x_2,… that is supposed to converge to the solution.
You will be asked to organize outputs of the method in a table where each line corresponds to one iteration.
The table will contain the following info:
i x_ix_i-x_{i-1} |x_i-x_(i-1)|/ |x_(i-1)-x_(i-2)|^k
where k is the convergence order of the method.
*/

double f(double x) {
    return x - cos(x);
}

double dfd(double x) {
    return 1 + sin(x);
}

double sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

VectorXd newtonsMethod(int iterations = 1) {
    VectorXd x;
    x.resize(iterations + 1);
    x(0) = 0;
    for (int i = 0; i < iterations; i++) {
        x(i + 1) = x(i) - f(x(i))/dfd(x(i));
    }
    return x;
}

VectorXd secantMethod(int iterations = 1) {
    VectorXd x;
    x.resize(iterations + 1);
    x(0) = 0;
    x(1) = M_PI/2;
    for (int i = 1; i < iterations; i++) {
        x(i + 1) = x(i) - (x(i) - x(i - 1)) / (f(x(i)) - f(x(i - 1))) * f(x(i));
    }
    return x;
}

VectorXd bisectionMethod(int iterations = 1) {
    VectorXd x;
    VectorXd y;
    x.resize(iterations + 1);
    y.resize(iterations + 1);
    x(0) = 0;
    y(0) = M_PI/2;
    for (int i = 0; i < iterations; i++) {
        x(i + 1) = (x(i) + y(i))/2;
        if((f(x(i + 1))*f(y(i))) < 0) {
            y(i + 1) = y(i);
        } else {
            y(i + 1) = x(i);
        }
    }
    return x;
}

VectorXd regulaFalsiMethod(int iterations = 1) {
    VectorXd x;
    VectorXd y;
    x.resize(iterations + 1);
    y.resize(iterations + 1);
    x(0) = 0;
    y(0) = M_PI/2;
    for (int i = 0; i < iterations; i++) {
        x(i + 1) = x(i) - (x(i) - y(i)) / (f(x(i)) - f(y(i))) * f(x(i));
        if((f(x(i + 1))*f(y(i))) < 0) {
            y(i + 1) = y(i);
        } else {
            y(i + 1) = x(i);
        }
    }
    return x;
}

VectorXd riddersMethod(int iterations = 1) {
    VectorXd x;
    VectorXd y;
    VectorXd z;
    x.resize(iterations + 1);
    y.resize(iterations + 1);
    z.resize(iterations + 1);

    x(0) = 0;
    y(0) = M_PI/2;

    for (int i = 0; i < iterations; i++) {
        z(i) = (x(i)+y(i))/2;
        x(i + 1) = z(i) + (z(i) - x(i)) * (sign(f(x(i))-f(y(i)))*f(z(i)))/(sqrt(pow(f(z(i)),2) - f(x(i)) * f(y(i))));
        if ((f(x(i + 1))*f(z(i))) < 0) {
            y(i + 1) = z(i);
        } else if ((f(x(i))*f(y(i))) < 0) {
            y(i + 1) = y(i);
        } else {
            y(i + 1) = x(i);
        }
    }
    return x;
}

void print(const VectorXd& v, double k) {
    if (true) {
        for (int i = 0; i < v.size(); i++) {
            if (i < 2) {
                cout << setw(5) << i << setw(15) << v(i) << setw(20) << v(i) - 0 << setw(48) << abs(v(i) - 0) / pow(abs(0 - 0), k) << setw(20) << "e[k]" << setw(0) << "C" << endl;
            } else if (i < 1) {
                cout << setw(5) << i << setw(15) << v(i) << setw(20) << v(i) - v(i - 1) << setw(48) << abs(v(i) - v(i - 1)) / pow(abs(v(i - 1) - 0), k) << setw(20) << "e[k]" << setw(0) << "C" << endl;
            } else {
                cout << setw(5) << i << setw(15) << v(i) << setw(20) << v(i) - v(i - 1) << setw(48) << abs(v(i) - v(i - 1)) / pow(abs(v(i - 1) - v(i - 2)), k) << setw(20) << "e[k]" << setw(0) << "C"
                     << endl;
            }
        }
    }
}

int main() {
    cout << fixed << setprecision(7) << left;
    cout << setw(5) << "i" << setw(15) << "x[i]" << setw(20) << "x[i] - x[i - 1]" << setw(48) << "|x[i] - x[i - 1]| / |x[i - 1] - x[i - 2]|^k" << setw(20) <<"e[k]" << setw(0) << "C" << endl;

    VectorXd newtonRes = newtonsMethod(5);
    cout << "\nNewton's method (k = 2):" << endl;
    print(newtonRes, 2);

    VectorXd secantRes = secantMethod(10);
    cout << "\nSecant method (k = 1.62):" << endl;
    print(secantRes, 1.62);

    VectorXd bisectionRes = bisectionMethod(30);
    cout << "\nBisection method (k = 1):" << endl;
    print(bisectionRes, 1);

    VectorXd regulaFalsiRes = regulaFalsiMethod(10);
    cout << "\nRegula Falsi method (k = 1):" << endl;
    print(regulaFalsiRes, 1);

    VectorXd riddersRes = riddersMethod(10);
    cout << "\nRidders method (k = 1):" << endl;
    print(riddersRes, 1);

    return 0;
}
