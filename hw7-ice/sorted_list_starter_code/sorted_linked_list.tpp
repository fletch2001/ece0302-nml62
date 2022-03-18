#include <stdexcept>

#include "sorted_linked_list.hpp"

template <typename T>
SortedLinkedList<T>::SortedLinkedList() : LinkedList<T>() {
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T>& x) : LinkedList<T>(x) {
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(const SortedLinkedList<T>& x) {
    LinkedList<T>::operator=(x);
    return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList() {
    // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() {
    return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() {
    return LinkedList<T>::getLength(); // return length
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item) {
    unsigned i = 1;
    while (i < LinkedList<T>::getLength() + 1) {
        if (item <= LinkedList<T>::getEntry(i)) { // insert at i if current list member is less than item
            LinkedList<T>::insert(i, item); 
            return;
        } else {
            i++; // otherwise, i++
        }
    }
    LinkedList<T>::insert(i, item);  // insert on end if not added in middle
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item) {
    if (isEmpty()) throw std::range_error("empty list in remove");

    for(unsigned i = 1; i < LinkedList<T>::getLength() + 1; i++) {
      if(LinkedList<T>::getEntry(i) == item) {
        LinkedList<T>::remove(i); // remove at index i if entry == item
        return; // return to call
      }
    }
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position) {
    if (isEmpty()) {throw std::range_error("empty list in remove");
    }; // throw if empty
      LinkedList<T>::remove(position + 1); // remove item
}

template <typename T>
void SortedLinkedList<T>::clear() {
    LinkedList<T>::clear(); // clear
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) {
    return LinkedList<T>::getEntry(position + 1); // return at LinkedList::getEntry(position+1)
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& newValue) {
    for(unsigned i = 1; i <= LinkedList<T>::getLength(); i++) {
      if(LinkedList<T>::getEntry(i) == newValue) { // return i - 1 if value found
        return --i;
      } else if (LinkedList<T>::getEntry(i) >= newValue) return --i; // if this value is greater than newValue, return i - 1
    }
  return getLength(); // otherwise, return current length (add onto end)
}