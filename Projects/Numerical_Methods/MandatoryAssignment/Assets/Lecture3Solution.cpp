#include <iostream>
#include <fstream>
#include <nr3.h>
#include <math.h>
#include <svd.h>
#include "utilities.h"


using namespace std;
using namespace util;

int main() {
	VecDoub xFilip(82); VecDoub yFilip(82);
	ifstream Filip("FilipData.dat"); // be aware of the path.
	for(int i = 0; i < 82; i++) {
		Filip >> yFilip[i];
		Filip >> xFilip[i];
	}

	MatDoub A(xFilip.size(),11);
	for(int i=0; i <A.nrows();i++ )
	{
		for(int j = 0; j < A.ncols(); j++)
			A[i][j]= pow(xFilip[i],(double) j);
	}

	//see NUMERICAL RECIPIES p. 69-70
	SVD SVD_A(A);
	VecDoub x(A.ncols());
	VecDoub x2(A.ncols());

	//Writing the solver yourself
	MatDoub U = SVD_A.u;
	MatDoub V = SVD_A.v;
	VecDoub W = SVD_A.w;

	MatDoub Winv = MatDoub(W.size(),W.size());
	for(int i = 0; i< W.size(); i++)
		Winv[i][i] = 1.0/W[i];

	x = V*Winv*T(U)*yFilip;
	//Alternatively using the NR3 solver with threshold value of eps
	SVD_A.solve(yFilip,x2,SVD_A.eps);
	cout << "Solution Filip using SVD:" << endl;
	x.print();
	x2.print();
	return 0;
}
