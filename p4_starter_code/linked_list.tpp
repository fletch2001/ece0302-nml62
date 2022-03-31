#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), length(0)
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear(); // use clear member
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  this->length = x.length;
  this->head = new Node<T>(x.head->getItem());
  Node<T> *temp = x.head->getNext();
  Node<T> *thisNext = head;
  while(temp != nullptr) {
    thisNext->setNext(new Node<T>(temp->getItem()));
    thisNext = thisNext->getNext();
    temp = temp->getNext();
  }
  temp = nullptr;
  thisNext = nullptr;
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
  Node<T> *tmpHead = x.head;
  size_t tmpSize = x.length;
  x.head = y.head;
  x.length = y.length;
  y.head = tmpHead;
  y.length = tmpSize;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& x)
{
  this->length = x.length;
  this->head = new Node<T>(x.head->getItem());
  Node<T> *temp = x.head->getNext();
  Node<T> *thisNext = head;
  while(temp != nullptr) {
    thisNext->setNext(new Node<T>(temp->getItem()));
    thisNext = thisNext->getNext();
    temp = temp->getNext();
  }
  temp = nullptr;
  thisNext = nullptr;
  return *this;
  // LinkedList<T> * tmp = new LinkedList<T>(x);
  // return *tmp;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  return (length == 0);
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return length;
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  if(position > length + 1 || position < 1) return false; // check that position is valid

  if(length == 0) {
    if(position != 1) return false;
    else {
      head = new Node<T>(item); // set head to new item
      ++length; // increase size
      return true;
    }
  } else if(position == 1) {
    head = new Node<T>(item, head); // set head to new node
    ++length;
    return true;
  } 
  else {
    Node<T> * next = head;
    for(unsigned i = 1; i < position - 1; i++) {
      next = next->getNext(); // traverse list until position - 1 node
    }
    Node<T> * temp = new Node<T>(item, next->getNext()); // make new node pointing to next node in chain
    next->setNext(temp); // set previous link to new node
    temp = nullptr;
    ++length; 
    return true;
  }
  return true;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if(position > 0 && position <= length) {
    if(position == 1) {
      Node<T> * temp = head->getNext();
      delete head;
      head = temp;
      --length;
      return true;
    } else {
    Node<T> * next = head;
    for(unsigned i = 1; i < position - 1; i++) {
      next = next->getNext(); // traverse list until at position - 1 node
    }
    Node<T> * removeNode = next->getNext(); // get pointer to node to remove
    next->setNext(removeNode->getNext()); // set pointer in position - 1 node to position + 1 node
    delete removeNode; // delete node at position
    removeNode = nullptr;

    --length;

    return true;
    }
  }
  return false;
}

template <typename T>
void LinkedList<T>::clear()
{
  while(!isEmpty()) {
    remove(1);
  }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  Node<T> * next = head;
  for(unsigned i = 1; i < position; i++) {
    next = next->getNext();
  }

  return next->getItem();
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  if(position > 0 && position <= length) {
    Node<T> *next = head;
    for(unsigned i = 1; i < position; i++) {
      next = next->getNext();
    }
    next->setItem(newValue);
  } else if(position == length + 1) insert(position, newValue);
}
