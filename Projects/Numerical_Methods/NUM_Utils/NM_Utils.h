//
// Created by Thomas Therkelsen on 20-06-2022.
// This header contains methods for doing vector/matrix calculations,
// root finding, numerical integrations, etc.
//

#ifndef NUM_UTILS_NM_UTILS_H
#define NUM_UTILS_NM_UTILS_H

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include <nr3.h>
#include <ludcmp.h>
#include <cholesky.h>
#include <svd.h>
#include <quadrature.h>
#include <derule.h>
#include <eigen_sym.h>
#include <eigen_unsym.h>

#include "utilities.h"

namespace nm_util {
    // Data loading

    MatDoub loadData(const string &path) {
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

        if (!inData) { // file couldn't be opened
            cerr << "Error: file could not be opened" << endl;
            exit(1);
        }

        int m, n;
        inData >> m >> n;
        MatDoub loadedData(m, n);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!inData.eof()) { // Only read data if not at the end of file
                    inData >> loadedData[i][j];
                }
            }
        }

        inData.close();

        return loadedData;
    }

    // Matrix handling methods
    MatDoub matTranspose(const MatDoub &m) {
        MatDoub transpose(m.nrows(), m.ncols());

        if (m.nrows() != m.ncols()) {
            throw std::invalid_argument("MatDoub must be square! (n x n)");
        } else {
            transpose.assign(transpose.nrows(), transpose.ncols(), 0);
            for (int i = 0; i < m.nrows(); i++) {
                for (int j = 0; j < m.ncols(); j++) {
                    if (m[i][j] != 0) {
                        transpose[i][j] = m[j][i];
                    }
                }
            }
        }
        return transpose;
    }

    MatDoub matInverse(const MatDoub &m) {
        // Computes the inverse vector
        MatDoub m_inv(m.nrows(), m.ncols());
        if (m.nrows() != m.ncols()) {
            throw std::invalid_argument("MatDoub must be square! (n x n)");
        } else {
            m_inv.assign(m_inv.nrows(), m_inv.ncols(), 0);
            for (int i = 0; i < m.nrows(); i++) {
                for (int j = 0; j < m.ncols(); j++) {
                    if (m[i][j] != 0) {
                        m_inv[i][j] = 1.0 / m[i][j];
                    }
                }
            }
        }
        return m_inv;
    }

    VecDoub matToVec(const MatDoub &m) {
        // Transforms single-column matrix to column vector
        VecDoub m_vec(m.nrows());

        for (int i = 0; i < m.nrows(); i++) {
            m_vec[i] = m[0][i];
        }
        return m_vec;
    }

    bool matEqual(const MatDoub &A, const MatDoub &B) {
        // Checks whether two matrices are equal
        if (A.nrows() != B.nrows() || A.nrows() != B.ncols()) {
            throw std::invalid_argument("MatDoubs must be same size!");
        } else {
            for (int i = 0; i < A.nrows(); i++) {
                for (int j = 0; j < A.ncols(); j++) {
                    if (A[i][j] != B[i][j]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool matSymmetric(const MatDoub &A) {
        // Checks whether a matrix is symmetric
        return matEqual(A, matTranspose(A));
    }

    bool matPosDef(const MatDoub &A) {
        // Checks whether matrix is positive definite
        // (Not always accurate due to limitations of accuracy in Cholesky)
        if (!matSymmetric(A)) {
            return false;
        }
        try {
            Cholesky Cho(A);
            return true;
        } catch (...) {
            return false;
        }
    } // NOT DONE

    // Vector handling methods
    bool vecEqual(const VecDoub &a, const VecDoub &b) {
        // Checks if two vectors are equal
        if (a.size() != b.size()) {
            return false;
        }
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }

    VecDoub vecSub(const VecDoub &org, const VecDoub &sub) {
        // Subtracts sub from org
        VecDoub subtractedVector;
        subtractedVector.assign(org.size(), 0);
        if (org.size() != sub.size()) {
            throw std::invalid_argument("VecDoubs must be of equal size!");
        } else {
            for (int i = 0; i < org.size(); i++) {
                subtractedVector[i] = org[i] - sub[i];
            }
        }
        return subtractedVector;
    }

    double vecNorm(const VecDoub &v) {
        // Computes the norm of v
        double sum = 0;

        for (int i = 0; i < v.size(); i++) {
            sum += pow(v[i], 2);
        }

        return sqrt(sum);
    }

    VecDoub vecNormalize(const VecDoub &v) {
        // Normalizes v
        VecDoub normalized = v;
        double _norm = vecNorm(normalized);
        for (int i = 0; i < normalized.size(); i++) {
            normalized[i] = normalized[i] / _norm;
        }
        return normalized;
    }

    VecDoub vecAbsolute(const VecDoub &v) {
        // Absolutes the elements of v
        VecDoub absolute = v;
        for (int i = 0; i < absolute.size(); i++) {
            absolute[i] = abs(absolute[i]);
        }
        return absolute;
    }

    VecDoub vecScale(const VecDoub &v, double s) {
        // Scales v with s
        VecDoub sv = v;
        for (int i = 0; i < sv.size(); i++) {
            sv[i] *= s;
        }
        return sv;
    }

    double vecDotProduct(const VecDoub &v1, const VecDoub &v2) { // Computes dot product between v1 and v2
        double dot = 0;
        for (int i = 0; i < v1.size(); i++) {
            dot += v1[i] * v2[i];
        }
        return dot;
    }

    vector<VecDoub> gramSchmidt(const vector<VecDoub> &x, const vector<VecDoub> &e, int K, int R) {
        // Applies the gram schmidt method to a set of vectors
        vector<VecDoub> gs;
        gs.reserve(K);
        for (int i = 0; i < R; i++) {
            gs[0][i] = x[0][i] / vecNorm(x[0]);
        }
        cout << "e[0]" << endl;
        util::print(gs[0]);

        VecDoub sum(5), temp(5);

        for (int i = 1; i < K; i++) {
            gs[i] = x[i];
            /*cout << "\nInitial e[" << i << "]" << endl;
            util::print(e[i]);*/
            sum.assign(sum.size(), 0);
            temp.assign(temp.size(), 0);
            for (int j = 0; j < i; j++) {
                // For every iteration, subtract from e[i] the vector e[j] scaled by the dot product between x[i] and e[j]
                temp = vecScale(gs[j], vecDotProduct(x[i], gs[j]));
                for (int k = 0; k < sum.size(); k++) {
                    sum[k] += temp[k];
                }
            }
            for (int j = 0; j < gs[i].size(); j++) {
                gs[i][j] -= sum[j];
            }
            gs[i] = vecNormalize(gs[i]);
            cout << "\ne[" << i << "] = " << endl;
            util::print(gs[i]);
        }
        return gs;
    }

    // Decomposition stuff
    VecDoub compLUD(const MatDoub &A, const VecDoub &b) {
        try {
            VecDoub x(size(b));
            LUdcmp LU(A);

            MatDoub _LU = LU.lu;

            MatDoub L = _LU;

            for (int i = 0; i < L.ncols(); i++) {
                for (int j = 0; j < L.nrows(); j++) {
                    if (i == j) {
                        L[i][j] = 1;
                    } else if (i < j) {
                        L[i][j] = 0;
                    }
                }
            }

            util::print(L, "L");

            MatDoub U = _LU;
            for (int i = 0; i < U.ncols(); i++) {
                for (int j = 0; j < U.nrows(); j++) {
                    if (i > j) {
                        U[i][j] = 0;
                    }
                }
            }

            util::print(U, "U");

            util::print(L * U, "L*U");

            LU.solve(b, x);
            util::print(x, "x solution computed by LUd");
            return x;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }

    MatDoub compLUDVariance(const MatDoub &A, const VecDoub &b) {
        try {
            VecDoub x(size(b));
            LUdcmp LU(A);
            LU.solve(b, x);
            MatDoub C;
            LU.inverse(C);

            util::print(C, "Variance C");

            return C;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return MatDoub{0, 0};
        }
    }

    VecDoub compCholesky(const MatDoub &A, const VecDoub &b) {
        if (!matPosDef(A)) {
            cerr << "Cholesky failed, matrix is not positive definite" << endl;
            return VecDoub{0};
        }
        try {
            VecDoub x(size(b));
            Cholesky Cho(A);

            Cho.solve(b, x);

            return x;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }

    MatDoub compCholeskyVariance(const MatDoub &A, const VecDoub &b) {
        if (!matPosDef(A)) {
            cerr << "Cholesky failed, matrix is not positive definite" << endl;
            return MatDoub{0, 0};
        }
        try {
            VecDoub x(size(b));
            Cholesky Cho(A);

            Cho.solve(b, x);
            MatDoub C;
            Cho.inverse(C);

            util::print(C, "Variance C");

            return C;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return MatDoub{0, 0};
        }
    }

    VecDoub compSVD(const MatDoub &A, const VecDoub &b) {
        try {
            VecDoub x(A.ncols());
            SVD SVD(A);

            SVD.solve(b, x, SVD.eps);

            return x;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }

    MatDoub compSVDU(const MatDoub &A, const VecDoub &b) {
        try {
            VecDoub x(A.ncols());
            SVD SVD(A);

            return SVD.u;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return MatDoub{0, 0};
        }
    }

    MatDoub compSVDV(const MatDoub &A, const VecDoub &b) {
        try {
            VecDoub x(A.ncols());
            SVD SVD(A);

            return SVD.v;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return MatDoub{0, 0};
        }
    }

    VecDoub compSVDW(const MatDoub &A, const VecDoub &b) {
        try {
            VecDoub x(A.ncols());
            SVD SVD(A);

            return SVD.w;
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }

    double compSVDEpsilonResiduals(const MatDoub &A, const MatDoub &b) {
        try {
            VecDoub b_vec = nm_util::matToVec(b);
            VecDoub x(A.ncols());
            SVD SVD(A);

            SVD.solve(b_vec, x, SVD.eps);

            VecDoub Ax = A * x;
            return nm_util::vecNorm(vecSub(Ax, b_vec)) / nm_util::vecNorm(b_vec);
        } catch (const std::exception &ex) {
            cerr << ex.what() << endl;
            return 0;
        }
    }

    double compResiduals(const VecDoub &Ax, const VecDoub &b) {
        return vecNorm(vecSub(Ax, b));
    }

    // Numerical integration
    template<class T>
    VecDoub numIntTrapezoidalMethod(T &f, const VecDoub &info) {
        // Uses the trapezoidal method to approximate the numerical integration of a given function

        int N = info[0]; // Number of initial subdivisions
        int maxIt = info[1]; // Number of iterations
        double a = info[2]; // lower bound
        double b = info[3]; // upper bound
        int acc = info[4]; // desired accuracy

        cout << scientific << "Attempting numerical integration by Trapezoidal method at accuracy of " << abs(1 * pow(10, (-acc))) << endl;

        VecDoub areas, areas2;
        areas.assign(maxIt, 0);

        for (int i = 0; i < maxIt; i++) {
            double h = (b - a) / (N - 1);

            double area = 0;
            area += 0.5 * f(a) + 0.5 * f(b);
            for (int j = 1; j < N - 1; j++) {
                area += f(a + h * j);
            }

            areas[i] = abs(area * h);
            N *= 2;

            if (i > 0) {
                if (abs(areas[i - 1] - areas[i]) < abs(pow(10, (-acc)))) {
                    cout << "Success: Reached accuracy of " << abs(pow(10, (-acc))) << ", terminating." << endl;
                    areas2.assign(i, 0);
                    break;
                } else if (i == maxIt - 1) {
                    cout << "Error: Exceeded maximum amount of iterations before reaching accuracy, terminating." << endl;
                    areas2.assign(i, 0);
                    break;
                }
            }
        }

        for (int i = 0; i < areas2.size(); i++) {
            areas2[i] = areas[i];
        }
        return areas2;
    }

    template<class T>
    VecDoub numIntExtendedMidpointMethod(T &f, const VecDoub &info) {
        // Uses the extended method to approximate the numerical integration of a given function
        int N = info[0]; // Number of initial subdivisions
        int maxIt = info[1]; // Number of iterations
        double a = info[2]; // lower bound
        double b = info[3]; // upper bound
        int acc = info[4]; // desired accuracy

        cout << scientific << "Attempting numerical integration by Extended Midpoint method at accuracy of " << abs(1 * pow(10, (-acc))) << endl;

        VecDoub areas, areas2;
        areas.assign(maxIt, 0);

        for (int i = 0; i < maxIt; i++) {
            double h = (b - a) / (N - 1);

            double area = 0;

            for (int j = 0; j < N - 1; j++) {
                area += f(a + h * j + h * 0.5);
            }

            areas[i] = abs(area * h);
            N *= 2;

            if (i > 0) {
                if (abs(areas[i - 1] - areas[i]) < abs(pow(10, (-acc)))) {
                    cout << "Success: Reached accuracy of " << abs(pow(10, (-acc))) << ", terminating." << endl;
                    areas2.assign(i, 0);
                    break;
                } else if (i == maxIt - 1) {
                    cout << "Error: Exceeded maximum amount of iterations before reaching accuracy, terminating." << endl;
                    areas2.assign(i, 0);
                    break;
                }
            }
        }

        for (int i = 0; i < areas2.size(); i++) {
            areas2[i] = areas[i];
        }
        return areas2;
    }

    template<class T>
    VecDoub numIntSimpsonsMethod(T &f, const VecDoub &info) {
        // Uses simpsons method to approximate the numerical integration of a given function
        int N = info[0]; // Number of initial subdivisions
        int maxIt = info[1]; // Number of iterations
        double a = info[2]; // lower bound
        double b = info[3]; // upper bound
        int acc = info[4]; // desired accuracy

        cout << scientific << "Attempting numerical integration by Simpsons method at accuracy of " << abs(1 * pow(10, (-acc))) << endl;

        VecDoub areas, areas2;
        areas.assign(maxIt, 0);

        for (int i = 0; i < maxIt; i++) {
            double h = (b - a) / (N - 1);

            double area = 1. / 3 * f(a) + 1. / 3 * f(b);
            for (int j = 1; j < N - 1; j++) {
                if (j % 2 != 0) {
                    area += 4. / 3 * f(a + h * j);
                } else {
                    area += 2. / 3 * f(a + h * j);
                }
            }
            areas[i] = abs(area * h);
            N *= 2;

            if (i > 0) {
                if (abs(areas[i - 1] - areas[i]) < abs(pow(10, (-acc)))) {
                    cout << "Success: Reached accuracy of " << abs(pow(10, (-acc))) << ", terminating." << endl;
                    areas2.assign(i, 0);
                    break;
                } else if (i == maxIt - 1) {
                    cout << "Error: Exceeded maximum amount of iterations before reaching accuracy, terminating." << endl;
                    areas2.assign(i, 0);
                    break;
                }
            }
        }

        for (int i = 0; i < areas2.size(); i++) {
            areas2[i] = areas[i];
        }
        return areas2;
    }

    template<class T>
    double numIntDerule(T &func, const double a, const double b, const double acc) {
        //VecDoub areas;

        Doub count = 0;
        Doub N = 0;
        Doub Ah0 = 0;
        Doub Ah1 = 0;
        DErule<T> rule(func, a, b, 4.3); //3.7    4.3  Vælges ud fra sværheden af singulariteten ved 1/sqrt(x) er 4.3 passende
        while ((abs(Ah0 - Ah1) / Ah0 > abs(1 * pow(10, (-acc))) || count == 0)) {
            count++;
            N = pow(2, count);
            Ah1 = Ah0;
            Ah0 = rule.next();
            cout << count << "  " << Ah0 << "   " << abs(Ah0 - Ah1) << endl;
            //areas[count] = Ah0;
        }
        return Ah0;
    }

    double richErrorEst(double alphak, const VecDoub &areas, int i) {
        // Estimates richardson error
        return abs((areas[i] - areas[i - 1]) / (alphak - 1));
    }

    double richAlphak(const VecDoub &areas, int i) {
        // Estimates alpha^k
        return abs(areas[i - 2] - areas[i - 1]) / abs(areas[i - 1] - areas[i]);
    }

    void numIntPrint(const VecDoub &areas, const VecDoub &info) {
        // Prints a nicely formatted table showing area, accuracy, richardson error, etc.
        int N = info[0];
        int maxIt = info[1];
        double a = info[2];
        double b = info[3];
        int acc = info[4];

        cout << fixed << setprecision(acc - 4) << left << setw(7) << "i" << setw(22) << "A(hi)" << setw(22) << "A(hi - 1) - A(hi)" << setw(22) << "Rich - alpha^k" << setw(22) << "Rich-error" << setw(16)
             << "F-Calculations" << endl;
        int fCalcs, prevFCalcs = 0;
        for (int i = 0; i < areas.size(); i++) {
            fCalcs += N - prevFCalcs;
            switch (i) {
                case 0:
                    cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << "*" << setw(22)
                         << "*" << setw(22) << "*" << setw(16) << fCalcs << endl;
                    break;
                case 1:
                    cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(22)
                         << "*" << setw(22) << richErrorEst(richAlphak(areas, i), areas, i) << setw(16) << fCalcs << endl;
                    break;
                case 2:
                    cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(22)
                         << "*" << setw(22) << richErrorEst(richAlphak(areas, i), areas, i) << setw(16) << fCalcs << endl;
                    break;
                default:
                    cout << setw(7) << i + 1 << setw(22) << areas[i] << setw(22) << areas[i - 1] - areas[i] << setw(22)
                         << richAlphak(areas, i) << setw(22) << richErrorEst(richAlphak(areas, i), areas, i) << setw(16) << fCalcs << endl;
                    break;
            }
            N *= 2;
            prevFCalcs = fCalcs;
        }
    }


    // Root finding
    // Inspiration is taken from Ole Wennerberg Nielsens examples uploaded to ItsLearning
    template<class T>
    Doub rootNewton(T &funcd, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int JMAX = 20;
        Doub rtn = 0.5 * (x1 + x2), dxOld = 9999;
        for (Int j = 0; j < JMAX; j++) {
            Doub f = funcd(rtn);
            Doub df = funcd.dc(rtn);
            Doub dx = f / df;

            cout << setw(15) << j + 1;
            cout << setw(15) << rtn;
            cout << setw(15) << dx;
            cout << setw(15) << abs(dx) / pow(abs(dxOld), 2);
            cout << setw(15) << 'e' << endl;
            dxOld = dx;

            rtn -= dx;
            if ((x1 - rtn) * (rtn - x2) < 0.0) throw("Jumped out of brackets in rootNewton");
            if (abs(dx) < xAccuracy) return rtn;
        }
        throw("Maximum number of iterations exceeded in rootNewton");
    }

    template<class T>
    Doub rootSecant(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int MAXIT = 30;
        Doub xl, rts, xOld = 9999;
        Doub fl = func(x1);
        Doub f = func(x2);
        if (abs(fl) < abs(f)) {
            rts = x1;
            xl = x2;
            SWAP(fl, f);
        } else {
            xl = x1;
            rts = x2;
        }
        for (Int j = 0; j < MAXIT; j++) {
            Doub dx = (xl - rts) * f / (f - fl);

            cout << setw(15) << j + 1;
            cout << setw(15) << rts;
            cout << setw(15) << dx;
            cout << setw(15) << abs(dx) / pow(abs(xOld - rts), 1.62);
            cout << setw(15) << 'e' << endl;
            xOld = rts;

            xl = rts;
            fl = f;
            rts += dx;
            f = func(rts);
            if (abs(dx) < xAccuracy || f == 0.0) return rts;
        }
        throw("Maximum number of iterations exceeded in rootSecant");
    }

    template<class T>
    Doub rootBisection(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int JMAX = 50;
        Doub dx, xmid, rtb, dxOld = 99999;
        Doub f = func(x1);
        Doub fmid = func(x2);
        if (f * fmid >= 0.0) throw("Root must be bracketed for bisection in rootBisection");
        rtb = f < 0.0 ? (dx = x2 - x1, x1) : (dx = x1 - x2, x2);
        for (Int j = 0; j < JMAX; j++) {
            cout << setw(15) << j + 1;
            cout << setw(15) << rtb;
            cout << setw(15) << rtb + dx;
            cout << setw(15) << dx;
            cout << setw(15) << dx / dxOld;
            cout << setw(15) << 'e' << endl;
            dxOld = dx;


            fmid = func(xmid = rtb + (dx *= 0.5));
            if (fmid <= 0.0) rtb = xmid;
            if (abs(dx) < xAccuracy || fmid == 0.0) return rtb;
        }
        throw("Too many bisections in rootBisection");
    }

    template<class T>
    Doub rootFalsePosition(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int MAXIT = 30;
        Doub xl, xh, del, delOldl = 0, delOldh = 0;
        Doub fl = func(x1);
        Doub fh = func(x2);
        if (fl * fh > 0.0) throw("Root must be bracketed in rootFalsePosition");
        if (fl < 0.0) {
            xl = x1;
            xh = x2;
        } else {
            xl = x2;
            xh = x1;
            SWAP(fl, fh);
        }
        Doub dx = xh - xl;
        for (Int j = 0; j < MAXIT; j++) {
            Doub rtf = xl + dx * fl / (fl - fh);
            Doub f = func(rtf);

            if (f < 0.0) {
                del = xl - rtf;
                xl = rtf;
                fl = f;

                cout << setw(15) << j + 1;
                cout << setw(15) << xl;
                cout << setw(15) << xh;
                cout << setw(15) << del;
                cout << setw(15) << del / delOldl;
                cout << setw(15) << 'e' << endl;
                delOldl = del;
                delOldh = 0;
            } else {
                del = xh - rtf;
                xh = rtf;
                fh = f;

                cout << setw(15) << j + 1;
                cout << setw(15) << xl;
                cout << setw(15) << xh;
                cout << setw(15) << del;
                cout << setw(15) << del / delOldh;
                cout << setw(15) << 'e' << endl;
                delOldl = 0;
                delOldh = del;
            }

            dx = xh - xl;
            if (abs(del) < xAccuracy || f == 0.0) return rtf;
        }
        throw("Maximum number of iterations exceeded in rootFalsePosition");
    }

    template<class T>
    Doub rootRidders(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const int MAXIT = 60;
        Doub fl = func(x1);
        Doub fh = func(x2);
        if ((fl > 0.0 && fh < 0.0) || (fl < 0.0 && fh > 0.0)) {
            Doub dx_old = 9.99e99;
            Doub xl = x1;
            Doub xh = x2;
            Doub ans = -9.99e99;
            for (Int j = 0; j < MAXIT; j++) {
                Doub xm = 0.5 * (xl + xh);
                Doub fm = func(xm);
                Doub s = sqrt(fm * fm - fl * fh);
                if (s == 0.0) return ans;
                Doub xnew = xm + (xm - xl) * ((fl >= fh ? 1.0 : -1.0) * fm / s);
                if (abs(xnew - ans) <= xAccuracy) return ans;

                Doub dx = xnew - ans;
                cout << setw(15) << j + 1;
                cout << setw(15) << xnew;
                cout << setw(15) << dx;
                cout << setw(15) << abs(dx) / pow(abs(dx_old), 2);
                cout << setw(15) << 'e' << endl;
                dx_old = dx;

                ans = xnew;
                Doub fnew = func(ans);
                if (fnew == 0.0) return ans;
                if (SIGN(fm, fnew) != fm) {
                    xl = xm;
                    fl = fm;
                    xh = ans;
                    fh = fnew;
                } else if (SIGN(fl, fnew) != fl) {
                    xh = ans;
                    fh = fnew;
                } else if (SIGN(fh, fnew) != fh) {
                    xl = ans;
                    fl = fnew;
                } else throw("never get here.");


                if (abs(xh - xl) <= xAccuracy) return ans;
            }
            throw("rootRidders exceed maximum iterations");
        } else {
            if (fl == 0.0) return x1;
            if (fh == 0.0) return x2;
            throw("root must be bracketed in rootRidders.");
        }
    }

    // ODE stuff
    template<class T, class Y>
    VecDoub IVPEuler(T &dxt, Y &dyt, double x0, double y0, int a, int b, int sub, int iterations) {
        double x = x0, xplus1 = 0;
        double y = y0, yplus1 = 0;

        double h = 0;

        int N = sub;

        VecDoub areas(iterations);

        for (int i = 0; i < iterations; i++) {
            h = (double(b) - double(a)) / double(N);
            x = x0;
            y = y0;

            for (double j = a; j < b; j = j + h) {
                xplus1 = x + h * dxt(x, y);
                yplus1 = y + h * dyt(x);
                x = xplus1;
                y = yplus1;
            }
            areas[i] = x;
            N *= 2;
        }

        return areas;
    }











    // Inspiration is taken from Ole Wennerberg Nielsens examples uploaded to ItsLearning
    double Euler(double x0, double y0, int a, int b, int hinv) {

        double x = x0;
        double y = y0;
        double t = a;
        double h = (double(b) - double(a)) / double(hinv);
        //std::cout << "Euler method, with h " << h << std::endl;
        //std::cout << "x(0) = " << x << std::endl;
        //std::cout << "y(0) = " << y << std::endl;
        //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
        //std::cout << std::endl;


        //for(double i = a; i< b-h; i = i+h)
        for (double i = a; i < b; i = i + h) {
            double xplus1 = x + h * (x * y);
            double yplus1 = y + h * (-pow(x, 2));
            x = xplus1;
            y = yplus1;
            t = t + h;
            //std::cout << "x(" << t << ") = " << x << std::endl;
            //std::cout << "y(" << t << ") = " << y << std::endl;
            //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
            //std::cout << std::endl;

        }
        //std::cout << "x(" << t << ") = " << x << std::endl;
        return (x);
    }

    double Leap_Frog(double x0, double y0, int a, int b, int hinv) {

        double x = x0;
        double y = y0;

        double t = a;
        double h = (double(b) - double(a)) / double(hinv);

        double xminus1 = x - h * (x * y);        // Using Euler
        double yminus1 = y - h * (-pow(x, 2));    // Using Euler

        //std::cout << "Leap_Frog method, with h " << h << std::endl;
        //std::cout << "x(0) = " << x << std::endl;
        //std::cout << "y(0) = " << y << std::endl;
        //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
        //std::cout << std::endl;

        for (double i = a; i < b; i = i + h) {
            double xplus1 = xminus1 + 2 * h * (x * y);
            double yplus1 = yminus1 + 2 * h * (-pow(x, 2));
            xminus1 = x;
            yminus1 = y;
            x = xplus1;
            y = yplus1;
            t = t + h;
            //	std::cout << "x(" << t << ") = " << x << std::endl;
            //	std::cout << "y(" << t << ") = " << y << std::endl;
            //	std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
            //	std::cout << std::endl;

        }
        return (x);

    }


    double Midpoint(double x0, double y0, int a, int b, int hinv) {

        double x = x0;
        double y = y0;

        double t = a;
        double h = (double(b) - double(a)) / double(hinv);
        //double h = 1.0/double(hinv);

        //std::cout << "Midpoint method, with h " << h << std::endl;
        //std::cout << "x(0) = " << x << std::endl;
        //std::cout << "y(0) = " << y << std::endl;
        //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
        //std::cout << std::endl;


        for (double i = a; i < b; i = i + h) {
            double xhalf = x + 0.5 * h * (x * y);
            double yhalf = y + 0.5 * h * (-pow(x, 2));

            double xplus1 = x + h * (xhalf * yhalf);
            double yplus1 = y + h * (-pow(xhalf, 2));
            x = xplus1;
            y = yplus1;
            t = t + h;
            //std::cout << "x(" << t << ") = " << x << std::endl;
            //std::cout << "y(" << t << ") = " << y << std::endl;
            //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
            //std::cout << std::endl;

        }
        //std::cout << "x(" << t << ") = " << x << std::endl;
        cout << t << endl;
        return (x);

    }


    double Trapezoidal(double x0, double y0, int a, int b, int hinv) {

        double x = x0;
        double y = y0;

        double t = a;
        double h = (double(b) - double(a)) / double(hinv);

        //std::cout << "Trapezoidal method, with h " << h << std::endl;
        //std::cout << "x(0) = " << x << std::endl;
        //std::cout << "y(0) = " << y << std::endl;
        //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
        //std::cout << std::endl;


        for (double i = a; i < b; i = i + h) {
            double xpluseuler = x + h * (x * y);
            double ypluseuler = y + h * (-pow(x, 2));

            double xplus1 = x + 0.5 * h * ((xpluseuler * ypluseuler) + (x * y));
            double yplus1 = y + 0.5 * h * ((-pow(xpluseuler, 2)) + (-pow(x, 2)));
            x = xplus1;
            y = yplus1;
            t = t + h;
            //std::cout << "x(" << t << ") = " << x << std::endl;
            //std::cout << "y(" << t << ") = " << y << std::endl;
            //std::cout << "x^2 + y^2 = " << pow(x,2)+pow(y,2) << std::endl;
            //std::cout << std::endl;

        }
        //cout << t << endl;
        return (x);
    }

    void rk4(const VecDoub &y, const VecDoub &dydx, const Doub x, const Doub h, VecDoub &yout, void derivs(const Doub, const VecDoub &, VecDoub &)) {
        Int n = y.size();
        VecDoub dym(n), dyt(n), yt(n);
        Doub hh = h * 0.5;
        Doub h6 = h / 6.0;
        Doub xh = x + hh;
        for (Int i = 0; i < n; i++) {
            yt[i] = y[i] + hh * dydx[i];// finding xn+1/2*k1
        }
        derivs(xh, yt, dyt);                            // finding f(xn+1/2*k1)	 (k2/h)
        for (Int i = 0; i < n; i++) {
            yt[i] = y[i] + hh * dyt[i];
        } // finding xn+1/2*k1
        derivs(xh, yt, dym);                            // finding f(xn+1/2*k2)  (k3/h)
        for (Int i = 0; i < n; i++) {
            yt[i] = y[i] + h * dym[i];                    // finding  xn+k3
            dym[i] += dyt[i];                        // Adding  f(xn+1/2k*1) and f(xn+1/2*k2) , that is (k2+k3)/h
        }
        derivs(x + h, yt, dyt);                            // finding f(xn+k3) k4/h
        for (Int i = 0; i < n; i++) {
            yout[i] = y[i] + h6 * (dydx[i] + dyt[i] + 2.0 * dym[i]);  //finding xn+1
        }
    }


    void rhs_van(const Doub x, VecDoub_I &y, VecDoub_O &dydx) {
        dydx[0] = y[0] * y[1];
        dydx[1] = -(y[0] * y[0]);
    }

    double compRK4(double x0, double y0, int a, int b, int hinv) {
        VecDoub z(2), dzdt(2), zold(2);
        z[0] = x0;
        z[1] = y0;

        double t = a;
        double h = (double(b) - double(a)) / double(hinv);
        for (double i = a; i < b; i = i + h) {
            rhs_van(t, z, dzdt);
            zold = z;
            rk4(zold, dzdt, t, h, z, rhs_van);
        }
        return z[0];
    }
}

#endif //NUM_UTILS_NM_UTILS_H
