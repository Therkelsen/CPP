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

//  Default constructor som laver et array med plads til ét element
template<typename T>
ArrayList<T>::ArrayList() {
    mElems = new T[1];
    mSize = 0;
    mReserved = 1;
}

//  Constructor som laver et array med plads med en given størrelse (initialized)
template<typename T>
ArrayList<T>::ArrayList(int initialized) {
    if (initialized > 0) {
        mElems      = new T[initialized];
        mSize       = 0;
        mReserved   = initialized;
    } else {
        throw std::invalid_argument("Size is not larger than 0");
    }
}

//  Copy-constructor som kopierer den reference man får som parameter, ind i et nyt array
template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> &c) {
    mElems      = new T[c.mReserved];
    mSize       = c.mSize;
    mReserved   = c.mReserved;

    for (int i = 0; i < c.mSize; i++) {
        mElems[i] = c.mElems[i];
    }
}

//  Move constructor som flytter den reference man får som parameter, ind i et nyt array
template<typename T>
ArrayList<T>::ArrayList(ArrayList<T> &&c) {
    mElems      = c.mElems;
    mSize       = c.mSize;
    mReserved   = c.mReserved;

    c.mElems    = nullptr;
    c.mReserved = 0;
    c.mSize     = 0;
}

//  Destructor som bare sletter arrayet
template<typename T>
ArrayList<T>::~ArrayList() {
    if (mSize > 0)
        delete[] mElems;
}

//  Copy assignment operator (arr1 = arr2;) som kopierer alle elementer fra referencen til et nyt array
template<typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &a) {
    if (mSize > 0)
        delete[] mElems;

    if (mReserved > 0)
        mElems = new T[a.mReserved];

    mSize = a.mSize;
    mReserved = a.mReserved;

    for (int i = 0; i < a.mSize; i++) {
        mElems[i] = a.mElems[i];
    }

    return *this;
}

//  Move assignment operator (arr1 = std::move(arr2);) som flytter alle elementer fra referencen til et nyt array
template<typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList<T> &&a) {
    if (mSize > 0)
        delete[] mElems;

    mElems      = a.mElems;
    mSize       = a.mSize;
    mReserved   = a.mReserved;

    a.mElems    = nullptr;
    a.mReserved = 0;
    a.mSize     = 0;

    return *this;
}

//  Laver et nyt array med dobbelt størrelse af originalen
template<typename T>
void ArrayList<T>::extendStorage() {
    T *arr = new T[mSize];
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

//  Firkant parentes operator som returnerer et const element på en given plads i arrayet
template<typename T>
const T &ArrayList<T>::operator[](int idx) const {
    if (idx < mSize) //
        return mElems[idx];
    else
        throw std::invalid_argument("Index out of bounds");
}

//  Firkant parentes operator som returnerer et element på en given plads i arrayet
template<typename T>
T &ArrayList<T>::operator[](int idx) {
    if (idx < mSize) //
        return mElems[idx];
    else
        throw std::invalid_argument("Index out of bounds");
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

//  Trimmer størrelsen på arrayet ned til minimum størrelse ved
//  at lave et nyt array med størrelsen af det gamle arrays mSize
template<typename T>
void ArrayList<T>::trimToSize() {
    if (mReserved > mSize) {
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
}

//  Sorterer arrayet med en bubble sort
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

//  Konverterer til C style array (helt normalt array)
template<typename T>
T *ArrayList<T>::toArray() {
    T *arr = new T[mSize];
    for (int i = 0; i < mSize; i++) {
        arr[i] = mElems[i];
    }

    return arr;
}

#endif //INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H
