#include "array_list.hpp"

template <typename T>
ArrayList<T>::ArrayList() {
  size = 0; // init size to 0
  arr = nullptr; // assign nullptr to arr
}

template <typename T>
ArrayList<T>::~ArrayList() {
  // delete array if array exists ( array will not be allocated until an item is inserted)
  if(arr) {
    if (size == 0) delete arr;
    else delete [] arr;
  }

  arr = nullptr; // set nullptr to arr
}

// copy constructor
template <typename T>
ArrayList<T>::ArrayList(const ArrayList & rhs) { 
  size = rhs.size; // set size

  arr = new T[size]; // allocate array

  for(unsigned i = 0; i < size; i++) {
    arr[i] = rhs.arr[i]; // copy items from rhs
  }
}

template <typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList & rhs){

  size = rhs.size; // copy size

  arr = new T[size]; // allocate new array of size copied from rhs

  for(unsigned i = 0; i < size; i++) {
    arr[i] = rhs.arr[i]; // assign items
  }

  return *this; // return new arraylist object
}

template <typename T>
bool ArrayList<T>::isEmpty() const{
  return !size; // return (size == 0)
}

template <typename T>
std::size_t ArrayList<T>::getLength() const{
  return size; // return arr size
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){
  if(position == 0) { // invalid input
    return false;
  } else if(size == 0 && position == 1) { // case when size is 0

    arr = new T[1];
    arr[0] = item;
    size = 1;

    return true;

  } else if(position == size + 1) { // when position is size of array. Extend by one element
    T * temp = new T[position]; // allocate new array for temp to be copied to arr later

    for(unsigned i = 0; i < size; i++) {
      temp[i] = arr[i]; // copt items from arr to temp
    }

    delete [] arr; // delete arr

    arr = temp; // assign temp to arr
    temp = nullptr; // assign nullptr to temp

    arr[size] = item; // assign item to last element and increase size

    size++;

    return true;

  } else if(position > 0 && position <= size) { // when position > 0 and < size, item must be inserted somewhere in middle of array
    
    T* temp = new T[size + 1]; // new temp array

    unsigned offset = 0; // initialize offset to 0

    for(unsigned i = 0; i < size; i++) { // copy items from original array to temp until index where item to be inserted is met
      if(i == position - 1) { // increase offset to 1 when index is at position to be inserted
        offset = 1; 
      }
        temp[i + offset] = arr[i]; // copy items from otiginal array
    }

    size++; // increase size
  
    temp[position - 1] = item; // insert new item

    delete [] arr; // delete original array

    arr = temp; // reassign temp to new array

    temp = nullptr;

    return true;
  /*} else if(position == size) {

    T* temp = new T[++size]; // new tmp array of size currentSize + 1
    temp = arr; // copy arr to tmp
    
    delete [] arr; // delete existing array

    temp[size - 1] = item; // set item at last position of temp

    arr = temp; // copy temp back to arr

    temp = nullptr; // set temp to nullptr

    return true; // return true

  }*/ 
  }else { // all other cases return false
    return false;
  }
}

template <typename T>
bool ArrayList<T>::remove(std::size_t position) {
  
  if(position <= size && position > 0) { // check that position is part of rance
    T* temp = new T[size - 1];

    for(unsigned i = 1, j = 0; i <= this->size; i++) {
      if(i == position) j++; // offset when element to not include in new array is met
      else temp[i - j - 1] = arr[i - 1]; // copy items to temp from arr
    }

    size--; // secrease size

    delete [] arr; // delete array
    arr = temp; // assign temp array to array
    temp = nullptr; // assign temp to nullptr

    return true; // return true if completed
  } else return false; // return false otherwise
}

template <typename T>
void ArrayList<T>::clear() {
  if(size == 0) delete arr;
  delete [] arr; // clear array / pointer
  
  arr = nullptr; // assign to nullptr

  size = 0; // set size to 0

}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  if(position > 0 && position < size + 1) return arr[position - 1]; // return item at position
  else return false; // return false if index is out of range
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if(position >= 1 && position <= size)
    arr[position - 1] = newValue;
  else;
}