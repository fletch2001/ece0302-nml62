#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  length = 0; // initialize length
  head = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  //TODO
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  //TODO
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  //TODO
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  //TODO
  return *this;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  return (length == 0); // return true if length = 0
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return length; // return length
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  if(length == 0 && position == 1) { // insert first node
    head = new Node<T>(item); // make new node
    length++; // increase length
    return true; // return true
  } else if(length == 0) {
    return false; // can't add in other positions if length == 0
  } else if(position <= length + 1) {
    Node<T> *nextNode = head;
    for(unsigned i = 0; i < position; i++) {
      nextNode = nextNode->getNext();
    }
    nextNode->setNext(new Node<T>(item)); // insert new node at end of list
    length++; // increase length
    return true;
  } else return false; // otherwise return false
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  //TODO
  return true;
}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //TODO
  return T();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}
