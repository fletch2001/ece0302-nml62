#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() {
  max_size = 20;
}

//copy constructor
template<typename T>
LimitedSizeBag<T>::LimitedSizeBag(const LimitedSizeBag& x) {
  // set max size and vector
  max_size = x.max_size;
  bag_vec = x.bag_vec;
}
    
// clear bag
template<typename T>
LimitedSizeBag<T>::~LimitedSizeBag() {
  bag_vec.clear();
}
  
// = operator
template<typename T>
LimitedSizeBag<T>& LimitedSizeBag<T>::operator=(LimitedSizeBag<T>& x)
{  
  //set max size and vector
  max_size = x.max_size;
  bag_vec = x.bag_vec;

  return *this;
}

// add
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  //check that bag is smaller than max size
  if(bag_vec.size() < max_size) {
    //push item to last position in bag
    bag_vec.push_back(item);

    return bag_vec[bag_vec.size() - 1] == item;
  } else {
    return false;
  }
}

// remove and resize
template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  for (unsigned i = 0; i < bag_vec.size(); i++) {
    if(bag_vec[i] == item) { 
    
      bag_vec.erase(bag_vec.begin() + i) ;

      //reclaim space
      bag_vec.resize(bag_vec.size());

      return true;
    }
  }
  return false;
}

// returns if empty == true
template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  return !bag_vec.size();
}

// returns size
template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return bag_vec.size();
}

// returns if contains specified item
template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  for(unsigned i = 0; i < bag_vec.size(); i++) {
    if(bag_vec[i] == item) return true;
  }
  return false;
}

// clears bag
template<typename T>
void LimitedSizeBag<T>::clear() {
  bag_vec.clear();
}

// returns frequency of item
template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  unsigned count = 0;
  for(T i : bag_vec) if(i == item) count++;
  return count;
}