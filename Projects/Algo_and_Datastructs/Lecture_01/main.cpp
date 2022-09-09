#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

unsigned int sum(unsigned int n) { // Returns the sum of the first n natural numbers
    if(n == 1)
        return 1;
    return n+sum(n-1);
}

unsigned int evenSquares(unsigned int n) { // returns the sum of the first n even numbers' squares
    if(n <= 1)
        return 0;
    else if (n % 2 == 0)
        return (int(pow(n,2)) + evenSquares(n - 2));
    return evenSquares(n - 1);
}

unsigned int fib(unsigned int n) {  // returns the nth Fibonacci number
    if (n <= 1)
        return n;
    return (fib(n - 1) + fib(n - 2));
}

bool linear(const string& s, char c, int l) {  // returns true if string s with the length l contains char c, otherwise false
    if(l < 1)
        return false;
    else if (s.at(l - 1) == c)
        return true;
    return linear(s,c,l - 1);
}

bool binarySearch(int list[], int val, int low, int high) {
    if (high >= low && !(high == low && high == val)) {
        int mid = (low + (high - low) / 2);
        if (list[mid] == val) // if val is at mid, then return true
            return true;

        if (val > list[mid]) // if val is on the right side of the midpoint
            return binarySearch(list, val, mid + 1, high);

        return binarySearch(list, val, low, mid - 1); // if val is on the left side of the midpoint
    }
    return false;
}

int main() {
    string s_ = "Therkelsen";
    char c_ = 'T';
    int l_ = int(s_.length());

    int size = 10;
    int start = 4;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i + start;
    }

    int value = 9;
    cout << boolalpha << binarySearch(arr, value, start, int(sizeof(arr) + start - 1)) << endl;
    return 0;
}
