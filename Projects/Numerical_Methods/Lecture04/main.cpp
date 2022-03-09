#include <iostream>
#include <iomanip>

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
    return y;
}

void print(const VectorXd& v) {
    //cout << setw(0) << "i" << setw(5) << "x_ix_i-x_{i-1}" << setw(10) << "|x_i-x_(i-1)|/ |x_(i-1)-x_(i-2)|^k" << endl;
    for (int i = 0; i < v.size(); i++) {
        cout << "x(" << i << ") = " << v(i) << endl;
    }
}

int main() {
    VectorXd newtonRes = newtonsMethod(5);
    cout << "Newton's method:" << endl;
    print(newtonRes);

    VectorXd secantRes = secantMethod(10);
    cout << "Secant method:" << endl;
    print(secantRes);

    VectorXd bisectionRes = bisectionMethod(20);
    cout << "Bisection method:" << endl;
    print(bisectionRes);

    return 0;
}
