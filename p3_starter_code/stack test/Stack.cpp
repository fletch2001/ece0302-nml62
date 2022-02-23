//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() 
{
	headPtr = nullptr; // set head pointer to nullptr
	currentSize = 0; // set current size to 0
}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
	clear(); // use clear method to destruct stack
}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	return currentSize == 0; // return true if size == 0
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize; // return size
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	currentSize++; // increase size
	Node<ItemType>* tmp = new Node<ItemType>(newItem); // new node with new item
	tmp->setNext(headPtr); // link current head to new node
	headPtr = tmp; // make new node the head
	tmp = nullptr; // set nullptr to tmp

	return (headPtr->getItem() == newItem); // check that the item has been successfully placed at the new node and return result of test
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const throw(logic_error)
{
	if(currentSize == 0) {
		throw logic_error("no items to access"); // throw if stack is empty
	} else {
		return headPtr->getItem(); // return item
	}
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if (currentSize == 0) {
		return false; // return false if size is 0 and there are no items to remove
	} else {
		currentSize--; // decrease current size
		Node<ItemType>* tmp = headPtr; // get head pointer
		headPtr = headPtr->getNext(); // set next node to headptr
		delete tmp; // delete previous head node
		tmp = nullptr; // assign nullptr to tmp pointer
		return true;
	}
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	if(currentSize != 0) {
		Node<ItemType>* tmp = headPtr;
		Node<ItemType>* next;

		while(currentSize > 1) {
			next = tmp->getNext(); // get pointer to next node
			delete tmp; // delete current node
			tmp = next; // set tmp to next
			currentSize--; // decrease currentsize
		}
		delete tmp; // delete last node
	
		currentSize--; // decrease size
		tmp = nullptr; // set nullptr to temp
		next = nullptr; // set nullptr to next
	}
	headPtr = nullptr; // set headptr to nullptr

}  // end clear

