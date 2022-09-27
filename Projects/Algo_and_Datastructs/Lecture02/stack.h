#ifndef LECTURE02_STACK_H
#define LECTURE02_STACK_H

#include <iostream>
#include <cstdlib>

// Define the default capacity of the stack
#define SIZE 10

// A class to represent a stack
class Stack {
    int *arr;
    int top;
    int capacity;

public:
    Stack(int size = SIZE);         // constructor
    ~Stack();                       // destructor
    void push(int);
    int pop();
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};


#endif //LECTURE02_STACK_H
