//
// Created by Thomas Therkelsen on 27-05-2021.
//

#ifndef INC_010618_PART1_BOX_H
#define INC_010618_PART1_BOX_H

template <class T>
class Box {
public:
    Box(int size = 10) {
        _l = 0; _b = 0; _h = 0; _size = size;
        if (size > 0)
            _array = new T[_size];
    }
    int size() {
        return _size;
    }
    Box(Box<T> &c);
    Box<T> &operator=(const Box<T> &a);
    virtual ~Box();
private:
    T* _array;
    int _size;
    int _l, _b, _h;
};

//  Copy-constructor som kopierer den reference man får som parameter, ind i et nyt array
template<class T>
Box<T>::Box(Box<T> &c) {
    _l = c._l;
    _b = c._b;
    _h = c._h;
    _size = c._size;

    if (_size > 0)
        _array = new T[_size];

    for (int i {0}; i < c._size; i++) {
        _array[i] = c._array[i];
    }
}

//  Copy-assignment operator som kopierer den reference man får som parameter, ind i et nyt array, og returnerer det
template<class T>
Box<T> &Box<T>::operator=(const Box<T> &c) {
    if (_size > 0) {
        delete[] _array;
        _array = new T[_size];
    }

    _l = c._l;
    _b = c._b;
    _h = c._h;
    _size = c._size;

    for (int i {0}; i < c._size; i++) {
        _array[i] = c._array[i];
    }

    return *this;
}

template<class T>
Box<T>::~Box() {
    delete[] _array;
}

#endif //INC_010618_PART1_BOX_H