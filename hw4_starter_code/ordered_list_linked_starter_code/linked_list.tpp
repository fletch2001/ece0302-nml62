#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  size = 0; // init size to 0
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
  return !size; // return size == 0
}

template <typename T>
std::size_t LinkedList<T>::getLength() const
{
  return size; // return size
}

template <typename T>
bool LinkedList<T>::insert(std::size_t position, const T& item)
{
  // first node
  if(position == 1 && size == 0) {
    
    size++; // increase size
    head = new Node<T>(item); // set head pointer to first node
    tail = head; // tail = head for 1 node list
    return true;

  } else if (position == size + 1) { // add new Node<T> on end
    
    size++; // increase size
    Node<T> * nextTail = new Node<T>(item); // make a new Node<T> for new tail
    tail->setNext(nextTail); // set current tail node next ptr to new tail
    tail = nextTail; // set tail to new node
    nextTail = nullptr; 
    return true;

  } else if (position > 1 && position <= size) { // inserting somewhere in middle: checks that position is valid and > 1 and < size

    size++; // increase size
    Node<T> * toAdd = new Node<T>(item); // make new node with item to insert
    Node<T> * posNode = head; // pointer to insert node at

    for(unsigned i = 0; i < position - 2; i++) {
      posNode = posNode->getNext(); // traverse list until at node before position to insert (position - 2)
    }

    Node<T> * afterInsert = posNode->getNext(); // get pointer to node after node to be inserted
    toAdd->setNext(afterInsert); // set next pointer in toAdd node to next node
    posNode->setNext(toAdd); // link previous node to new insertion node

    // set working pointers to nullptr
    toAdd = nullptr;
    posNode = nullptr; 

    return true; // return true
  }
  return false;
}

template <typename T>
bool LinkedList<T>::remove(std::size_t position)
{
  if(position == 1) { // remove first node: head needs to be reset
    size--; // decrease size

    Node<T> *delNode = head; // get pointer to first node
    head = head->getNext(); // set head to next node

    delete delNode; // delete node to be removed
    delNode = nullptr; // set removed node pointer to nullptr

    return true; // return true

  } else if(position == size) { // remove last node: tail needs to be reset
    size--; // decrease size

    Node<T> *newTail = head;
    for(unsigned i = 0; i < position - 2; i++) { // get pointer to node before tail
      newTail = newTail->getNext();
    }

    delete tail; // delete tail (last) node
    tail = newTail; // set tail to node before previous tail

    return true;

  }
  if(position > 1 && position <= size) {
    --size;

    Node<T> * nextNode = head; // pointer to node to re-link (node after node to be removed)

    for(unsigned i = 0; i < position - 2; i++ ) { // traverse to two nodes before node to be removed to obtain pointer to node to be removed
      nextNode = nextNode->getNext();
    }

    Node<T> * delNode = nextNode->getNext(); // node to delete

    nextNode->setNext((delNode->getNext())); // link node before delete node to node after

    delete delNode; // delete node to be removed

    // set pointers to nullptr
    delNode = nullptr; 
    nextNode = nullptr;
    

    return true; // return true
  }

  return false; // return false for all invalid cases
}

template <typename T>
void LinkedList<T>::clear()
{
    Node<T> * nextNode = head;
    Node<T> * delNode = head; // pointer to current node and next node
    while(size > 0) { // loop until at node before tail
      delNode = nextNode;
      nextNode = delNode->getNext(); // get pointer to next node
      delete delNode; // delete current node
      size--; // decrease size
    }
    //delete tail; // delete tail node

    // assign all pointers to nullptr
    tail = nullptr;
    delNode = nullptr;
    nextNode = nullptr;
    head = nullptr;

}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  if(position <= size && position > 0) { // checks for valid position
    Node<T> * next = head; // pointer to next node is first node: head
    for(unsigned i = 0; i < position - 1 ; i++) { // get pointer to each next node until next points to last node (position - 2 node)
      next = next->getNext();
    }
    return next->getItem(); // return item at node
  }
  return false;
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
}

/*

position = 3

call 0
next = head (node 0)

call 1
next = node 1

call 2
next = node 2

*/