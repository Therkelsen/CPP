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

#include "utilities.h"

namespace nm_util {
    // Data loading
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

    // Matrix handling methods
    MatDoub matInverse(const MatDoub& m) {
        // Computes the inverse vector
        MatDoub m_inv(m.nrows(), m.ncols());
        if(m.nrows() != m.ncols()) {
            throw std::invalid_argument("MatDoub must be square! (n x n)");
        } else {
            m_inv.assign(m_inv.nrows(), m_inv.ncols(), 0);
            for (int i = 0; i < m.nrows(); i++) {
                for (int j = 0; j < m.ncols(); j++) {
                    if(m[i][j] != 0) {
                        m_inv[i][j] = 1.0 / m[i][j];
                    }
                }
            }
        }
        return m_inv;
    }
    VecDoub matToVec(const MatDoub& m){
        // Transforms single-column matrix to column vector
        VecDoub m_vec(m.nrows());

        for (int i = 0; i < m.nrows(); i++) {
            m_vec[i] = m[0][i];
        }
        return m_vec;
    }

    // Vector handling methods
    bool vecEqual(const VecDoub& a, const VecDoub& b) {
        // Checks if two vectors are equal
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
    VecDoub vecSub(const VecDoub& org, const VecDoub& sub){
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
    double vecNorm(const VecDoub& v) {
        // Computes the norm of v
        double sum = 0;

        for (int i = 0; i < v.size(); i++) {
            sum += pow(v[i], 2);
        }

        return sqrt(sum);
    }
    VecDoub vecNormalize(const VecDoub& v) {
        // Normalizes v
        VecDoub normalized = v;
        double _norm = vecNorm(normalized);
        for (int i = 0; i < normalized.size(); i++) {
            normalized[i] = normalized[i] / _norm;
        }
        return normalized;
    }
    VecDoub vecAbsolute(const VecDoub& v) {
        // Absolutes the elements of v
        VecDoub absolute = v;
        for (int i = 0; i < absolute.size(); i++) {
            absolute[i] = abs(absolute[i]);
        }
        return absolute;
    }

    // Decomposition stuff
    VecDoub compLUD(const MatDoub& A, const VecDoub& b) {
        try {
            VecDoub x(size(b));
            LUdcmp LU(A);

            MatDoub _LU = LU.lu;
            util::print(_LU, "L*U");

            LU.solve(b,x);
            util::print(x, "x solution computed by LUd");
            return x;
        } catch (const std::exception & ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }
    MatDoub compLUDVariance(const MatDoub& A, const VecDoub& b){
        try {
            VecDoub x(size(b));
            LUdcmp LU(A);
            LU.solve(b,x);
            MatDoub C;
            LU.inverse(C);
            return C;
        } catch (const std::exception & ex) {
            cerr << ex.what() << endl;
            return MatDoub{0, 0};
        }
    }
    VecDoub compCholesky(const MatDoub& A, const VecDoub& b){
        try {
            VecDoub x(size(b));
            Cholesky Cho(A);

            Cho.solve(b,x);

            return x;
        } catch (const std::exception & ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }
    MatDoub compCholeskyVariance(const MatDoub& A, const VecDoub& b){
        try {
            VecDoub x(size(b));
            Cholesky Cho(A);

            Cho.solve(b,x);
            MatDoub C;
            Cho.inverse(C);
//            util::print(A,"A");
//            util::print(L*U,"L*U");
//            util::print(L*U*x,"L*U*x");
//            util::print(x,"x");

            return C;
        } catch (const std::exception & ex) {
            cerr << ex.what() << endl;
            return MatDoub{0, 0};
        }
    }
    VecDoub compSVD(const MatDoub& A, const VecDoub& b) {
        try {
            VecDoub x(A.ncols());
            SVD SVD(A);

            SVD.solve(b,x,SVD.eps);

            return x;
        } catch (const std::exception & ex) {
            cerr << ex.what() << endl;
            return VecDoub{0};
        }
    }
    double compSVDEpsilonResiduals(const MatDoub& A, const MatDoub& b){
        try {
            VecDoub b_vec = nm_util::matToVec(b);
            VecDoub x(A.ncols());
            SVD SVD(A);

            SVD.solve(b_vec,x,SVD.eps);

//            util::print(A,"A");
//            util::print(L*U,"L*U");
//            util::print(L*U*x,"L*U*x");
//            util::print(x,"x");

            VecDoub Ax = A*x;
            return nm_util::vecNorm(vecSub(Ax, b_vec))/nm_util::vecNorm(b_vec);
        } catch (const std::exception & ex) {
            cerr << ex.what() << endl;
            return 0;
        }
    }

    // Root finding
    // Some inspiration is taken from Ole Wennerberg Nielsens examples uploaded to ItsLearning
    template <class T>
    Doub rootNewton(T &funcd, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int JMAX=20;
        Doub rtn=0.5*(x1+x2), dxOld=9999;
        for (Int j=0;j<JMAX;j++) {
            Doub f=funcd(rtn);
            Doub df = funcd.dc(rtn);
            Doub dx=f/df;

            cout << setw(15) << j+1;
            cout << setw(15) << rtn;
            cout << setw(15) << dx;
            cout << setw(15) << abs(dx)/pow(abs(dxOld),2);
            cout << setw(15) << 'e' << endl;
            dxOld = dx;

            rtn -= dx;
            if ((x1-rtn)*(rtn-x2) < 0.0)
            throw("Jumped out of brackets in rootNewton");
            if (abs(dx) < xAccuracy) return rtn;
        }
        throw("Maximum number of iterations exceeded in rootNewton");
    }

    template <class T>
    Doub rootSecant(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int MAXIT=30;
        Doub xl,rts,xOld = 9999;
        Doub fl=func(x1);
        Doub f=func(x2);
        if (abs(fl) < abs(f)) {
            rts=x1;
            xl=x2;
            SWAP(fl,f);
        } else {
            xl=x1;
            rts=x2;
        }
        for (Int j=0;j<MAXIT;j++) {
            Doub dx=(xl-rts)*f/(f-fl);


            cout << setw(15) << j+1;
            cout << setw(15) << rts;
            cout << setw(15) << dx;
            cout << setw(15) << abs(dx)/pow(abs(xOld- rts),1.62);
            cout << setw(15) << 'e' << endl;
            xOld = rts;

            xl=rts;
            fl=f;
            rts += dx;
            f=func(rts);
            if (abs(dx) < xAccuracy || f == 0.0) return rts;
        }
        throw("Maximum number of iterations exceeded in rootSecant");
    }

    template <class T>
    Doub rootBisection(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int JMAX=50;
        Doub dx,xmid,rtb,dxOld = 99999;
        Doub f=func(x1);
        Doub fmid=func(x2);
        if (f*fmid >= 0.0) throw("Root must be bracketed for bisection in rootBisection");
        rtb = f < 0.0 ? (dx=x2-x1,x1) : (dx=x1-x2,x2);
        for (Int j=0;j<JMAX;j++) {
            cout << setw(15) << j+1;
            cout << setw(15) << rtb;
            cout << setw(15) << rtb+dx;
            cout << setw(15) << dx;
            cout << setw(15) << dx/dxOld;
            cout << setw(15) << 'e' << endl;
            dxOld =dx;


            fmid=func(xmid=rtb+(dx *= 0.5));
            if (fmid <= 0.0) rtb=xmid;
            if (abs(dx) < xAccuracy || fmid == 0.0) return rtb;
        }
        throw("Too many bisections in rootBisection");
    }

    template <class T>
    Doub rootFalsePosition(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const Int MAXIT=30;
        Doub xl,xh,del, delOldl = 0,delOldh = 0;
        Doub fl=func(x1);
        Doub fh=func(x2);
        if (fl*fh > 0.0) throw("Root must be bracketed in rootFalsePosition");
        if (fl < 0.0) {
            xl=x1;
            xh=x2;
        } else {
            xl=x2;
            xh=x1;
            SWAP(fl,fh);
        }
        Doub dx=xh-xl;
        for (Int j=0;j<MAXIT;j++) {
            Doub rtf=xl+dx*fl/(fl-fh);
            Doub f=func(rtf);

            if (f < 0.0) {
                del=xl-rtf;
                xl=rtf;
                fl=f;

                cout << setw(15) << j+1;
                cout << setw(15) << xl;
                cout << setw(15) << xh;
                cout << setw(15) << del;
                cout << setw(15) << del/delOldl;
                cout << setw(15) << 'e' << endl;
                delOldl = del;
                delOldh = 0;
            } else {
                del=xh-rtf;
                xh=rtf;
                fh=f;

                cout << setw(15) << j+1;
                cout << setw(15) << xl;
                cout << setw(15) << xh;
                cout << setw(15) << del;
                cout << setw(15) << del/delOldh;
                cout << setw(15) << 'e' << endl;
                delOldl = 0;
                delOldh = del;
            }


            dx=xh-xl;
            if (abs(del) < xAccuracy || f == 0.0) return rtf;
        }
        throw("Maximum number of iterations exceeded in rootFalsePosition");
    }

    template <class T>
    Doub rootRidders(T &func, const Doub x1, const Doub x2, const Doub xAccuracy) {
        const int MAXIT=60;
        Doub fl=func(x1);
        Doub fh=func(x2);
        if ((fl > 0.0 && fh < 0.0) || (fl < 0.0 && fh > 0.0)) {
            Doub dx_old = 9.99e99;
            Doub xl=x1;
            Doub xh=x2;
            Doub ans=-9.99e99;
            for (Int j=0; j<MAXIT; j++)
            {
                Doub xm=0.5*(xl+xh);
                Doub fm=func(xm);
                Doub s=sqrt(fm*fm-fl*fh);
                if (s == 0.0) return ans;
                Doub xnew=xm+(xm-xl)*((fl >= fh ? 1.0 : -1.0)*fm/s);
                if (abs(xnew-ans) <= xAccuracy) return ans;

                Doub dx = xnew - ans;
                cout << setw(15) << j+1;
                cout << setw(15) << xnew;
                cout << setw(15) << dx;
                cout << setw(15) << abs(dx)/pow(abs(dx_old),2);
                cout << setw(15) << 'e' << endl;
                dx_old = dx;

                ans=xnew;
                Doub fnew=func(ans);
                if (fnew == 0.0) return ans;
                if (SIGN(fm,fnew) != fm) {
                    xl=xm;
                    fl=fm;
                    xh=ans;
                    fh=fnew;
                } else if (SIGN(fl,fnew) != fl) {
                    xh=ans;
                    fh=fnew;
                } else if (SIGN(fh,fnew) != fh) {
                    xl=ans;
                    fl=fnew;
                } else throw("never get here.");


                if (abs(xh-xl) <= xAccuracy) return ans;
            }
            throw("rootRidders exceed maximum iterations");
        }
        else {
            if (fl == 0.0) return x1;
            if (fh == 0.0) return x2;
            throw("root must be bracketed in rootRidders.");
        }
    }

    // Numerical Integration
    // Some inspiration is taken from Ole Wennerberg Nielsens examples uploaded to ItsLearning
    template<class T>
    Doub numIntExtendedMidpoint(T& func, const Doub a, const Doub b, const Doub eps = 1.0e-10) {
        const Int JMAX = 20;
        Doub s, olds = 0.0, oldolds = 0.0, rn = 0.0, r = 0.0, oldr = 0.0, oldoldr = 0.0;
        Midpnt<T> t(func, a, b); 	for (Int j = 0; j < JMAX; j++) {
            s = t.next();
            cout << setw(15) << j + 1;
            cout << setw(15) << s;
            if (oldolds > 0.0) { cout << setw(15) << log((oldolds - olds) / (olds - s))/log(3); } //Note the log(3) is added to change it to "log3" instead of "log"
            else { cout << setw(15) << " "; }
            if (olds > 0.0) { r = s + (s - olds) /8.0; cout << setw(15) << r; } // We see that k1 tends towards 2,and with alpha=3 we get alpha^k-1 = 8
            else { cout << setw(15) << " "; }
            if (oldoldr > 0.0) { cout << setw(15) << log((oldoldr - oldr) / (oldr - r)) / log(3); }
            else { cout << setw(15) << " "; }
            if (oldr > 0.0) { rn = r + (r - oldr) /80.0; cout << setw(15) << rn; } // We see that k2 tends towards 4,and with alpha=3 we get alpha^k-1 = 80
            else { cout << setw(15) << " "; }
            cout << endl;


            if (j > 5)
                if (abs(s - olds) < eps * abs(olds) ||
                    (s == 0.0 && olds == 0.0)) return s;

            oldoldr = oldr;
            oldolds = olds;
            oldr = r;
            olds = s;

        }
        cout << "Too many steps in routine qtrap" << endl;
        return s;
        throw("Too many steps in routine qtrap");
    }

    template<class T>
    Doub numIntTrapezoidal(T &func, const Doub a, const Doub b, const Doub eps=1.0e-10) {
        const Int JMAX=30;
        Doub s, olds = 0.0 , oldolds =0.0,rn=0.0, r=0.0, oldr = 0.0,oldoldr=0.0 ;
        Trapzd<T> t(func,a,b);
        //Midpnt<T> t(func,a,b); //Choose between midpoint or trapezoidal method here
        for (Int j=0;j<JMAX;j++) {
            s=t.next();
            cout << setw(15) << j+1;
            cout << setw(15) << s;
            if (oldolds > 0.0){ cout << setw(15) << log2((oldolds-olds)/(olds-s));}
            else {cout << setw(15) << " ";}
            if (olds > 0.0){ r=s+(s-olds)/3;cout << setw(15) << r;} // We see that k1 tends towards 2,and with alpha=2 we get alpha^k-1 = 3
            else {cout << setw(15) << " ";}
            if (oldoldr > 0.0){ cout << setw(15) << log2((oldoldr-oldr)/(oldr-r));}
            else {cout << setw(15) << " ";}
            if (oldr > 0.0){ rn=r+(r-oldr)/15;cout << setw(15) << rn;} // We see that k2 tends towards 4,and with alpha=2 we get alpha^k-1 = 15
            else {cout << setw(15) << " ";}
            cout << endl;


            if (j > 5)
                if (abs(s-olds) < eps*abs(olds) ||
                    (s == 0.0 && olds == 0.0)) return s;

            oldoldr =oldr;
            oldolds=olds;
            oldr=r;
            olds=s;

        }
        cout << "Too many steps in routine qtrap" << endl;
        return s;
        throw("Too many steps in routine qtrap");
    }

    template<class T>
    double numIntDerule(T &func, const double a, const double b, const double pre)
    {
        Doub count = 0;
        Doub N = 0;
        Doub Ah0 = 0;
        Doub Ah1 = 0;
        DErule<T> rule(func, a, b, 4.3); //3.7    4.3  Vælges ud fra sværheden af singulariteten ved 1/sqrt(x) er 4.3 passende
        while( (abs(Ah0-Ah1)/Ah0 > pre || count==0) )//&& count < 16384 )
        {
            count++;
            N = pow(2,count);
            Ah1=Ah0;
            Ah0 = rule.next();
            cout << count << "  " << Ah0 << "   " << abs(Ah0-Ah1) << endl;
        }
        return Ah0;
    }

}

#endif //NUM_UTILS_NM_UTILS_H
