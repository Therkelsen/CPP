#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstdlib>

#include <Eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

MatrixXd loadData(){
    MatrixXd loadedData;

    ifstream inData;
    inData.open("../Assets/Ex1A.dat");

    if(!inData) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }

    float num;
    inData >> num;
    int i = 0;
    int cols, rows;
    while (!inData.eof() ) { // keep reading until end-of-file
        cout << "The next number is " << num << endl;
        cout << "i = " << i << endl;
        inData >> num; // sets EOF flag if no value found
        if (i == 0) {
            rows = num;
        } else if (i == 1) {
            cols = num;
            loadedData.resize(rows, cols);
        } else {
            
        }
        i++;
    }

    inData.close();
    cout << "End-of-file reached.." << endl;

    return loadedData;
}

int main() {
    MatrixXd data;
    int cols, rows;

    loadData();


    return 0;
}
