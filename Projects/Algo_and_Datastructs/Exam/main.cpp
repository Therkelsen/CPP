#include <iostream>
#include <cmath>
#include <algorithm>
#include "BinarySearchTree.h"

int secondLargestElem(int arr[], int length){
    if(length < 3)
        return -1;
    std::cout << arr[length-1] << " " << arr[length-2] << " " << arr[length-3] << std::endl;
    if(arr[length-1] < arr[length-2]) {
        if(arr[length-2] < arr[length-3]) {
            int temp = arr[length - 1];
            arr[length - 1] = arr[length - 2];
            arr[length - 2] = temp;
            return secondLargestElem(arr, length-3);
        }
    }
}

int main() {
    int arr[] = {23,117,10,14,18,22,29,39,51,45,49,61,65,68,81,89};

    std::cout << std::size(arr) << std::endl;
    int res = secondLargestElem(arr, std::size(arr));
//    BinarySearchTree BST;
//    BST.insert(1);
//    BST.insert(2);
//    BST.insert(10231);
//    BST.printTree();
    return 0;
}
