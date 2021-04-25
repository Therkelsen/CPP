//
// Created by Thomas Therkelsen on 21-04-2021.
//

#ifndef INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H
#define INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H

#include <iostream>

template<typename T>
class ArrayList {
public:
    ArrayList();

    //Copy constructor
    ArrayList(ArrayList<T> &c);

    //move constructor
    ArrayList(ArrayList<T> &&c);

    //constructor with initialization of
    // "initialized elements
    ArrayList(int initialized);

    virtual ~ArrayList();

    //Copy assignment operator
    ArrayList<T> &operator=(const ArrayList<T> &a);

    //move assignment operator
    ArrayList<T> &operator=(ArrayList<T> &&a);

    //Add element to dynamic array
    void add(const T &element);

    void add(int idx, const T &element);

    const T &operator[](int idx) const;

    T &operator[](int idx);

    void remove(int idx);

    int size() const;

    int reserved() const;

    bool isEmpty() const;

    void trimToSize();

    void sort();

    ArrayList<T> subArrayList(int fromIdx, int toIdx) const;

    T *toArray();


private:
    void extendStorage();

    int mReserved;
    int mSize;
    T *mElems;
};

//  Default constructor
template<typename T>
ArrayList<T>::ArrayList() {
    mElems = new T[1];
    mSize = 0;
    mReserved = 1;
}

//  Constructor med given størrelse
template<typename T>
ArrayList<T>::ArrayList(int initialized) {
    mElems = new T[initialized];
    mSize = 0;
    mReserved = initialized;
}

//  Copy-constructor
template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> &c) {
    mElems = new T[c.mReserved];
    mSize = c.mSize;
    mReserved = c.mReserved;

    for (int i = 0; i < c.mSize; i++) {
        mElems[i] = c.mElems[i];
    }
}

//  Move constructor
template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> &&c) {
    mElems = c.mElems;
    mSize = c.mSize;
    mReserved = c.mReserved;

    c.mElems = nullptr;
    c.mReserved = 0;
    c.mSize = 0;
}

//  Destructor
template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] mElems;
}

//  Copy assignment operator (arr1 = arr2;)
template<typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &a) {
    delete[] mElems;
    mElems = new T[a.mReserved];
    mSize = a.mSize;
    mReserved = a.mReserved;

    for (int i = 0; i < a.mSize; i++) {
        mElems[i] = a.mElems[i];
    }
    return *this;
}

//  Move assignment operator (arr1 = std::move(arr2);)
template<typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList<T> &&a) {
    delete[] mElems;
    mElems = a.mElems;
    mSize = a.mSize;
    mReserved = a.mReserved;

    a.mElems = nullptr;
    a.mReserved = 0;
    a.mSize = 0;

    return *this;
}

//  Fordobler størrelsen af arrayet
template<typename T>
void ArrayList<T>::extendStorage() {
    T *arr = new T[mReserved * 2];
    for (int i = 0; i < mSize; i++) {
        arr[i] = mElems[i];
    }
    delete[] mElems;
    mElems = new T[mReserved * 2];
    for (int i = 0; i < mSize; i++) {
        mElems[i] = arr[i];
    }
    delete[] arr;
    mReserved *= 2;
}

//  Tilføjer et nyt givent element i arrayet
template<typename T>
void ArrayList<T>::add(const T &element) {
    if (mSize == mReserved) {
        extendStorage();
    }
    mElems[mSize] = element;
    mSize++;
}

//  Tilføjer et nyt element på idx plads i array,
//  og rykker resten af elementerne én plads frem
template<typename T>
void ArrayList<T>::add(int idx, const T &element) {
    if (mSize == mReserved) {
        extendStorage();
    }

    T value;
    mElems[mSize] = value;
    for (int i = mSize; i > idx; i--) {
        mElems[i] = mElems[i - 1];
    }
    mElems[idx] = element;
    mSize++;
}

//  Firkant parentes operator
template<typename T>
const T &ArrayList<T>::operator[](int idx) const {
    return mElems[idx];
}

//  Const firkant parentes operator
template<typename T>
T &ArrayList<T>::operator[](int idx) {
    return mElems[idx];
}

//  Fjerner et element fra idx plads og rykker resten én tand
template<typename T>
void ArrayList<T>::remove(int idx) {
    for (int i = idx; i < mSize; i++) {
        mElems[i] = mElems[i + 1];
    }
    mSize--;
}

//  Returnerer størrelsen af arrayet
template<typename T>
int ArrayList<T>::size() const {
    return mSize;
}

//  Returnerer mængden af reserverede pladser i arrayet
template<typename T>
int ArrayList<T>::reserved() const {
    return mReserved;
}

//  Tjekker om arrayet er tomt
template<typename T>
bool ArrayList<T>::isEmpty() const {
    if (mSize > 0) {
        return false;
    } else {
        return true;
    }
}

//  Trimmer størrelsen på arrayet ned til minimum størrelse
template<typename T>
void ArrayList<T>::trimToSize() {
    T *arr = new T[mSize];

    for (int i = 0; i < mSize; i++) {
        arr[i] = mElems[i];
    }
    delete[] mElems;
    mElems = new T[mSize];

    for (int i = 0; i < mSize; i++) {
        mElems[i] = arr[i];
    }
    delete[] arr;
    mReserved = mSize;
}

//  Sorterer arrayet med en insertion sort
template<typename T>
void ArrayList<T>::sort() {

    for (int i = 0; i < mSize - 1; i++) {
        for (int j = i + 1; j < mSize; j++) {
            if (mElems[i] > mElems[j]) {
                auto temp = mElems[j];
                mElems[j] = mElems[i];
                mElems[i] = temp;
            }
        }
    }
}

//  Danner et nyt array fra fromIdx til og med toIdx
template<typename T>
ArrayList<T> ArrayList<T>::subArrayList(int fromIdx, int toIdx) const {
    ArrayList<T> a1;
    for (int i = fromIdx; i <= toIdx; i++) {
        a1.add(mElems[i]);
    }
    return a1;
}

//  Konverterer til C style array
template<typename T>
T *ArrayList<T>::toArray() {
    T *arr = new T[mSize];
    for (int i = 0; i < mSize; i++) {
        arr[i] = mElems[i];
    }

    return arr;
}

#endif //INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H
