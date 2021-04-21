#include <iostream>
#include "ArrayList.h"

int main() {
    ArrayList<double> array;

    for (int i = 0; i < 33; ++i) {
        array.add(i*1.1) ;
    }


    array.add(4, -5);
    array.remove(1);

    for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << ", ";
    }
/*
    std::cout << "\b\b " << std::endl << std::endl;



    std::cout << " ArrayList have reserved space for " << array.reserved()
    << " elements and stores " << array.size() << "elements ." << std::endl;

    array.trimToSize();

    std::cout << "ArrayList is now trimmed and have reserved space for " << array . reserved ()
    << " elements and stores " << array.size() << " elements ." << std::endl << std::endl;


    ArrayList<double> subArray = array.subArrayList(1, 10);

    std::cout << "Sub ArrayList have reserved space for " << subArray.reserved()
    << " elements and stores " << subArray.size() << " elements ." << std::endl;

    for (int i = 0; i < subArray.size(); ++i) {
        std::cout << subArray[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;

    double *sArray = subArray.toArray();

    for (int i = 0; i < 7; ++i) {
        subArray.add(i + 1);
    }

    // The basic array prints after adding elements to subArray
    std::cout << " Basic array of sub array contains : " << std::
    endl;
    for (int i = 0; i < subArray.size() - 7; ++i) {
        std::cout << sArray[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;

    // The sub array now has elements
    std::cout << "Sub array with 7 elements added : " << std::endl;
    for (int i = 0; i < subArray.size(); ++i) {
        std::cout << subArray[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;

    // The original array has
    std::cout << " Original array " << std::endl;
    for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << ", ";
    }
    std::cout << "\b\b " << std::endl;

    // Copy constructor
    // Copy assignment
    ArrayList<double> array2 = array;
    ArrayList<double> subArray2;
    subArray2 = subArray;

    std::cout << " array2 = ";
    for (int i = 0; i < array2.size(); ++i) {
        std::cout << array2[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;

    std::cout << " subArray2 = ";
    for (int i = 0; i < subArray2.size(); ++i) {
        std::cout << subArray2[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;

    // Move assignment operator
    ArrayList<double> subArray3 = std::move(subArray2);
    array2 = std::move(subArray2);

    std::cout << " subArray2 = ";
    for (int i = 0; i < subArray2.size(); ++i) {
        std::cout << subArray2[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;

    std::cout << " subArray3 = ";
    for (int i = 0; i < subArray3.size(); ++i) {
        std::cout << subArray3[i] << ", ";
    }
    std::cout << "\b\b " << std::endl << std::endl;
    */
    return 0;
}