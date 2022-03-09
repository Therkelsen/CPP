#include <iostream>
#include <iomanip>
#include <math.h>

#include <Eigen/Dense>

#include "../Assets/NR_C301/code/nr3.h"
#include "../Assets/NR_C301/code/utilities.h"

using namespace std;

double norm(const VecDoub& v) { // Computes the norm of v
    double sum = 0;

    for (int i = 0; i < v.size(); i++) {
        sum += pow(v[i], 2);
    }

    return sqrt(sum);
}

VecDoub normalize(const VecDoub& v) { // Normalizes v
    VecDoub normalized = v;
    double _norm = norm(normalized);
    for (int i = 0; i < normalized.size(); i++) {
        normalized[i] = normalized[i] / _norm;
    }
    return normalized;
}

double dotProduct(const VecDoub& v1, const VecDoub& v2) { // Computes dot product between v1 and v2
    double dot = 0;
    for (int i = 0; i < v1.size(); i++) {
        dot += v1[i]*v2[i];
    }
    return dot;
}

VecDoub scale(const VecDoub& v, double s) { // Scales v with s
    VecDoub sv = v;
    for (int i = 0; i < sv.size(); i++) {
        sv[i] *= s;
    }
    return sv;
}

VecDoub subtract(const VecDoub& v, const VecDoub& s) { // Subtracts s from v
    VecDoub temp = v;
    for (int i = 0; i < temp.size(); i++) {
        temp[i] -= s[i];
    }
    return temp;
}

VecDoub zeros(const VecDoub& v) { // Fills v with zeros
    VecDoub zeros = v;
    for (int i = 0; i < zeros.size(); i++) {
        zeros[i] = 0;
    }
    return zeros;
}

int main() {
    cout << fixed << setprecision(5);

    int K = 3; // Amount of vectors
    int R = 5; // Dimension

    VecDoub x1(R), x2(R), x3(R), e1(R), e2(R), e3(R);

    x1[0] = 2; x1[1] = 8; x1[2] = 4; x1[3] = 2; x1[4] = 1;
    x2[0] = 1; x2[1] = 1; x2[2] = 5; x2[3] = 7; x2[4] = 8;
    x3[0] = 4; x3[1] = -5; x3[2] = 1; x3[3] = -4; x3[4] = 3;

    e1 = zeros(e1); e2 = zeros(e2); e3 = zeros(e3);

    vector<VecDoub> x, e;
    x.reserve(K); e.reserve(K);

    x.emplace_back(x1); x.emplace_back(x2); x.emplace_back(x3);
    e.emplace_back(e1); e.emplace_back(e2); e.emplace_back(e3);

    for (int i = 0; i < R; i++) {
        e[0][i] = x[0][i] / norm(x[0]);
    }
    cout << "e[0]" << endl;
    util::print(e[0]);

    VecDoub sum(5), temp(5);

    for (int i = 1; i < K; i++) {
        e[i] = x[i];
        /*cout << "\nInitial e[" << i << "]" << endl;
        util::print(e[i]);*/
        sum = zeros(sum); temp = zeros(temp);
        for (int j = 0; j < i; j++) {
            // For every iteration, subtract from e[i] the vector e[j] scaled by the dot product between x[i] and e[j]
            temp = scale(e[j], dotProduct(x[i],e[j]));
            for (int k = 0; k < sum.size(); k++) {
                sum[k] += temp[k];
            }
            /*cout << "\nAt (i,j) = (" << i << "," << j << "):" << endl;
            cout << "\ndp = " << dotProduct(x[i],e[j] ,R) << endl;
            cout << "\nscale = " << endl;
            util::print(scale(e[j], dotProduct(x[i],e[j] ,R),R));
            cout << "\nsubtraction = " << endl;
            util::print(subtract(e[i], scale(e[j], dotProduct(x[i],e[j] ,R),R),R));*/
        }
        for (int j = 0; j < e[i].size(); j++) {
            e[i][j] -= sum[j];
        }
        e[i] = normalize(e[i]);
        cout << "\ne[" << i << "] = " << endl;
        util::print(e[i]);
    }

    return 0;
}
