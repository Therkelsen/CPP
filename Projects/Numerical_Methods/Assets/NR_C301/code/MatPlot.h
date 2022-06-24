/*
 * MatlabPlot.h
 *
 *  Created on: May 24, 2022
 *      Author: own
 *  Visual Studio Setup steps:
 *  	Configuration Properties --> Debugging --> Environment: 		               PATH=C:\Program Files\MATLAB\R2019b\bin\win64;
 *  	Configuration Properties --> C/C++ --> General -->  Additional Include Directories: C:\Program Files\MATLAB\R2019b\extern\include;
 *  	Configuration Properties --> Linker --> General --> Additional Library Directories: C:\Program Files\MATLAB\R2019b\extern\lib\win64\microsoft;
 *  	Configuration Properties --> Linker --> Input --> Additional Dependcies:            libmx.lib;libmat.lib;libeng.lib;
 *
 */

//#ifndef MATPLOT_H_
//#define MATPLOT_H_


//#include "nr3.h"
#include "engine.h"


//namespace MatPlot
//{
    int engPutVariable_func(Engine& m_pEngine, VecDoub TheVector, string MatVarName)
    {
        /*This function will put a column vector in MATLAB Workspace*/

        int SIZE = TheVector.size();

        double* Temp = new double[SIZE];


        for (int i = 0; i < SIZE; i++)
        {
            Temp[i] = TheVector[i];
        }

        char Char_VariableName[1000];
        strcpy_s(Char_VariableName, MatVarName.c_str());

        /* Creating Matlab Variables*/

        mxArray* TheMatVec = NULL;
        TheMatVec = mxCreateDoubleMatrix(SIZE, 1, mxREAL);
        memcpy((void*)mxGetPr(TheMatVec), (void*)Temp, sizeof(Temp) * SIZE);
        engPutVariable(&m_pEngine, Char_VariableName, TheMatVec);

        //    delete[] Temp;

        return 0;
    }
    int Create_2DArray_in_Matlab(Engine& m_pEngine, MatDoub PlotData, string MatVarName)
    {
        /*Approach is to convert matrix to a vector, send to matlab and reshape back intro matrix
         *in Matlab workspace*/

        int SIZE_rows = PlotData.nrows();
        int SIZE_cols = PlotData.ncols();
        VecDoub Sizes(2);
        Sizes[0] = SIZE_rows;
        Sizes[1] = SIZE_cols;
        int SIZE_total = SIZE_rows * SIZE_cols;
        VecDoub Temp(SIZE_total);
        int i;
        for (int n = 0; n < SIZE_rows; n++)
        {
            for (int m = 0; m < SIZE_cols; m++)
            {
                i = n + m * SIZE_rows;
                Temp[i] = PlotData[n][m];
            }
        }
        string Evalstring = MatVarName + "= reshape(" + MatVarName + ", Temp_Sizes(1), Temp_Sizes(2))";
        engPutVariable_func(m_pEngine, Temp, MatVarName);
        engPutVariable_func(m_pEngine, Sizes, "Temp_Sizes");
        engEvalString(&m_pEngine, Evalstring.c_str());
        engEvalString(&m_pEngine, "clear Temp_Sizes");

        return 0;
    }

//}

/* Example
* int main()
* {
* Engine *eng;
* eng=engOpen(""); // put a breakpoint here
*
* //engSetVisible(eng, 1);
* //engEvalString(eng, "clc;");
* //engEvalString(eng, "close all;");
* //engEvalString(eng, "clear all;");
* //engEvalString(eng, "workspace");
*
* MatDoub A(3, 3);
* A[0][0] = 1.0;	A[0][1] = 2.0;	A[0][2] = 3.0;
* A[1][0] = 2.0;	A[1][1] = -4.0;	A[1][2] = 6.0;
* A[2][0] = 3.0;	A[2][1] = -9.0;	A[2][2] = -3.0;
*
* Create_2DArray_in_Matlab(*eng, A, "AMatrix");
*
* VecDoub b(3);
* b[0] = 5.0;
* b[1] = 18.0;
* b[2] = 6.0;
* engPutVariable_func(*eng, b , "bVector");
*
* engEvalString(eng, "Plot(AMatrix");
*
*
* //engClose(eng);     // put a breakpoint here
*
* return 0;
* }
*/

//#endif /* MATPLOT_H_ */