#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "dynamic_array_list.h"

template <typename T>
DynamicArrayList<T>::DynamicArrayList() {
    capacity = 10;
    size = 0;
    data = new T[capacity];
}

template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList<T>& x) {
    this->size = x.size;           // copy size
    this->capacity = x.capacity;   // copy capacity
    this->data = new T[capacity];  // new data array

    for (unsigned i = 0; i < x.size; i++) {
        this->data[i] = x.data[i];  // copy data
    }
}

template <typename T>
DynamicArrayList<T>::~DynamicArrayList() {
    std::clog << "DynamicArrayList Destructor called." << std::endl;

    delete[] data; // delete data
    data = nullptr; // nullptr to data
    
}

template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> x) {
    this->size = x.getLength();           // copy size
    this->capacity = 10 + this->size / 10;   // copy capacity
    this->data = new T[capacity];  // new data array

    for (unsigned i = 0; i < this->size; i++) {
        this->data[i] = x.getEntry(i);  // copy data
    }

    return *this;
}

template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& y) {
    // collect members of y
    T* thisData = y.data;
    std::size_t thisCapacity = y.capacity;
    std::size_t thisSize = y.size;

    // set data from this to y
    y.data = this->data;
    y.capacity = this->capacity;
    y.size = this->size;

    // set data from y to this
    this->data = thisData;
    this->capacity = thisCapacity;
    this->size = thisSize;

    // nullptr
    thisData = nullptr;
}

template <typename T>
bool DynamicArrayList<T>::isEmpty() {
    return (size == 0);
}

template <typename T>
std::size_t DynamicArrayList<T>::getLength() {
    return size;
}

template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& item) {
    if (position > size + 1 || position < 0) throw(std::range_error("illegal position"));

    if (size + 1 > capacity) {
        capacity += 10;  // increase capacity
        // DynamicArrayList<T>* temp = new DynamicArrayList<T>(*this);

        // delete this;

        // *this = *temp;  // set new object to this
        // temp = nullptr;

        // reallocate array to new capacity
        T* temp = new T[capacity];
        for (unsigned i = 0; i < size; i++) {
            temp[i] = data[i];
        }

        delete[] data;
        data = temp;
    }

    if (position == size) {
        data[position] = item;  // set item
        size++;                 // increase size
    } else {
        T* temp = new T[size++];

        for (unsigned i = 0, os = 0; i < size - 1; i++) {
            if (i == position) {
                ++os;            // set offset to 1
                temp[i] = item;  // set item
            }
            temp[i + os] = data[i];  // copy members of data to temp
        }

        delete[] data;
        data = temp;

        temp = nullptr;
    }
}

template <typename T>
void DynamicArrayList<T>::remove(std::size_t position) {
    if (position > size - 1 || position < 0) throw(std::range_error("illegal position"));

    if (position == size - 1) {
        data[position] = 0;
        size--;
    } else {
        T* temp = new T[size - 1];
        for (int i = 0, os = 0; i < size; i++) {
            if (i == position) {
                --os; // decrement offset
                continue;
            }
            temp[i + os] = data[i]; // copy member of data
        }
        delete[] data; // delete data array
        data = temp; // assign temp to data
        temp = nullptr;
        --size; // decremement size
    }
}

template <typename T>
void DynamicArrayList<T>::clear() {
    delete [] data; // delete data
    data = new T[capacity]; // reallocate with current capacity
    size = 0;
}

template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position) {
    if (position > size - 1 || size < 0) throw(std::range_error("illegal position"));
    return data[position];
}

template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue) {
    if (position > size - 1 || size < 0) throw(std::range_error("illegal position"));

    data[position] = newValue;
}