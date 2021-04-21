//
// Created by Thomas Therkelsen on 21-04-2021.
//

#ifndef INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H
#define INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H

#include <iostream>


template <typename T>
class ArrayList
{
public:
    ArrayList();

    //Copy constructor
    ArrayList(ArrayList<T>& c);


    //move constructor
    ArrayList(ArrayList<T>&& c);


    //constructor with initialization of
    // "initialized elements
    ArrayList(int initialized);

    virtual ~ArrayList();

    //Copy assignment operator
    ArrayList<T>& operator=(const ArrayList<T>& a);


    //move assignment operator
    ArrayList<T>& operator=(ArrayList<T>&& a);

    //Add element to dynamic array
    void add(const T& element);

    void add(int idx, const T& element);

    const T& operator [](int idx) const;

    T& operator[](int idx);

    void remove(int idx);

    int size() const;

    int reserved() const;

    bool isEmpty() const;

    void trimToSize();

    void sort();

    ArrayList<T> subArrayList(int fromIdx, int toIdx) const;

    T* toArray();


private:
    void extendStorage();

    int mReserved;
    int mSize;
    T* mElems;
};


template<typename T>
ArrayList<T>::ArrayList(){
    mElems = new T[1];
    mSize = 0;
    mReserved = 1;
}

/*
template<typename T>
ArrayList<T>::ArrayList(int initialized){

}
*/


//copy-constructor
template<typename T>
ArrayList<T>::ArrayList(ArrayList<T>& c){
    mElems = new T[c.mReserved];
    mSize = c.mSize;
    mReserved = c.mReserved;

    for(int i = 0; i < c.mSize; i++){
        mElems[i] = c.mElems[i];
    }
}



//move constructor
template<typename T>
ArrayList<T>::ArrayList(ArrayList<T>&& c){
    mElems = std::move(c.mElems);
    mSize = std::move(c.mSize);
    mReserved = std::move(c.mReserved);

    for(int i = 0; i < c.mSize; i++){
        mElems[i] = std::move(c.mElems[i]);
    }
}



template<typename T>
ArrayList<T>::~ArrayList(){
    delete[] mElems;
}



template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& a){
    delete[] mElems;
    mElems = new T[a.mReserved];
    mSize = a.mSize;
    mReserved = a.mReserved;

    for(int i = 0; i < a.mSize; i++){
        mElems[i] = a.mElems[i];
    }
    return *this;
}


template<typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& a){
    mElems = std::move(a.mElems);
    mSize = std::move(a.mSize);
    mReserved = std::move(a.mReserved);

    for(int i = 0; i < a.mSize; i++){
        mElems[i] = std::move(a.mElems[i]);
    }
    return *this;
}


template<typename T>
void ArrayList<T>::extendStorage(){
    T* arr = new T[mReserved*2];
    for(int i = 0; i < mSize; i++){
        arr[i] = mElems[i];
    }
    delete [] mElems;
    mElems = new T[mReserved*2];
    for(int i = 0; i < mSize; i++){
        mElems[i] = arr[i];
    }
    mReserved *= 2;
}


template<typename T>
void ArrayList<T>::add(const T& element){
    if(mSize == mReserved){
        extendStorage();
    }
    mElems[mSize] = element;
    mSize++;
}


template<typename T>
void ArrayList<T>::add(int idx, const T& element){
    if(mSize == mReserved){
        extendStorage();
    }

    for (int i = idx; i < mSize-2; i++){
        auto temp = mElems[i+1];
        mElems[i+1] = mElems[i];
        mElems[i+2] = temp;
    }
    mElems[idx] = element;
    mSize++;
}

template<typename T>
const T& ArrayList<T>::operator[](int idx) const{
    return mElems[idx];
}

template<typename T>
T& ArrayList<T>::operator[](int idx){
    return mElems[idx];
}


template<typename T>
void ArrayList<T>::remove(int idx){

    for (int i = mSize + 2; i > idx; i--){
        auto temp = mElems[i-1];
        mElems[i-1] = mElems[i];
        mElems[i-2] = temp;
    }
    //  mElems[mSize] = nullptr;
    mSize--;
}


template <typename T>
int ArrayList<T>::size() const{
    return mSize;
}


template <typename T>
int ArrayList<T>::reserved() const{
    return mReserved;
}



template <typename T>
bool ArrayList<T>::isEmpty() const{
    if(mSize > 0){
        return false;
    }else{
        return true;
    }
}


template <typename T>
void ArrayList<T>::trimToSize(){
    T* arr = new T[mSize];

    for(int i = 0; i < mSize; i++){
        arr[i] = mElems[i];
    }
    delete[] mElems;
    mElems = new T[mSize];

    for(int i = 0; i < mSize; i++){
        mElems[i] = arr[i];
    }

    mReserved = mSize;
}

template <typename T>
void ArrayList<T>::sort(){

    for (int i = 0; i < mSize - 1; i++){
        for(int j = i + 1; j < mSize; j++){
            if(mElems[i] > mElems[j]){
                auto temp = mElems[j];
                mElems[j] = mElems[i];
                mElems[i] = temp;
            }
        }
    }
}


//Vi antager at det er fra og med formIdx og til og med toIdx
template <typename T>
ArrayList<T> ArrayList<T>::subArrayList(int fromIdx, int toIdx) const{
    ArrayList<T> a1;
    for(int i = fromIdx; i <= toIdx; i++){
        a1.add(mElems[i]);
    }
    return a1;
}

// Arrayet mister sin "reserved" - egenskab og bliver fyldt helt ud med
// tal.
template <typename T>
T* ArrayList<T>::toArray(){
    T* arr = new T[mSize];
    for(int i = 0; i < mSize; i++){
        arr[i] = mElems[i];
    }

    return arr;
}


#endif //INC_18_1_TEMPLATE_ARRAYLIST_ARRAYLIST_H
