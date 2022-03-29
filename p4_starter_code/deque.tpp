#include "deque.hpp"

template<typename T>
Deque<T>::Deque() : AbstractDeque<T>(), size(0)
{}

// copy assignment
template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T> &) {

}

// destructor 
template<typename T>
Deque<T>::~Deque() 
{
}

/** Returns true if the deque is empty, else false
 */
template<typename T>
bool Deque<T>::isEmpty() const noexcept {
    return (size == 0);
}

/** Add item to the front of the deque
 * may throw std::bad_alloc
 */
template<typename T>
void Deque<T>::pushFront(const T & item) {
    dlst.insert(1, item);
    ++size;
}

/** Remove the item at the front of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
void Deque<T>::popFront() {
    if(isEmpty()) throw std::runtime_error("deque is empty");
    else dlst.remove(1);
    --size;
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
    dlst.insert(++size, item);
}

/** Remove the item at the back of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
void Deque<T>::popBack() {
    if(isEmpty() == true) throw std::runtime_error("deque empty");
    else dlst.remove(size--);
}

/** Returns the item at the back of the deque
 * throws std::runtime_error if the deque is empty
 */
template<typename T>
T Deque<T>::back() const {
    if(isEmpty() == true) throw std::runtime_error("deque empty");
    else return dlst.getEntry(size);
}