#include "deque.hpp"

// default constructor: use AbstractDQ default constructor and linked list constructor is called upon object instantiation
template<typename T>
Deque<T>::Deque() : AbstractDeque<T>()
{}

// copy constructor
template<typename T>
Deque<T>::Deque(const Deque & q) {
    this->dlst = q.dlst;
}

//copy assignment
template<typename T>
Deque<T>& Deque<T>::operator=(const Deque & q) {
    this->dlst = q.dlst;
    return *this;
}

// destructor 
template<typename T>
Deque<T>::~Deque() 
{
    dlst.clear(); // just to be safe, this is done automatically anyways
}

/** Returns true if the deque is empty, else false
 */
template<typename T>
bool Deque<T>::isEmpty() const noexcept {
    return dlst.isEmpty();
}

/** Add item to the front of the deque
 * may throw std::bad_alloc
 */
template<typename T>
void Deque<T>::pushFront(const T & item) {
    dlst.insert(1, item);
}

/** Remove the item at the front of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
void Deque<T>::popFront() {
    if(isEmpty()) throw std::runtime_error("deque is empty");
    else dlst.remove(1);
}

/** Returns the item at the front of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
T Deque<T>::front() const {
    if(isEmpty()) throw std::runtime_error("deque is empty");
    else return dlst.getEntry(1);
}

/** Add item to the back of the deque
 * may throw std::bad_alloc
 */
template<typename T>
void Deque<T>::pushBack(const T & item) {
    dlst.insert(dlst.getLength() + 1, item);
}

/** Remove the item at the back of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
void Deque<T>::popBack() {
    if(isEmpty() == true) throw std::runtime_error("deque empty");
    else dlst.remove(dlst.getLength());
}

/** Returns the item at the back of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
T Deque<T>::back() const {
    if(isEmpty() == true) throw std::runtime_error("deque empty");
    else return dlst.getEntry(dlst.getLength());
}