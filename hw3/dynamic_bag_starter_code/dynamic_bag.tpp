#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() {
  bag_size = 0;
}
  

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag& x){
  // set size and get pointer to reference bag
  this->bag_size = x.getCurrentSize();
  this->bag_arr = new T[bag_size];
  T* copy_ptr = x.bag_arr;
  
  // copy items to new bag
  for(unsigned int i = 0; i < this->bag_size; i++){
    this->bag_arr[i] = copy_ptr[i];
  }

  copy_ptr = nullptr;
}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){
  
  // deallocate memory
  if(bag_size > 0) delete [] bag_arr;
  else delete bag_arr;
  bag_arr = nullptr;
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T>& x)
{ 
  // get size and pointer to reference bag
  this->bag_size = x.getCurrentSize();
  this->bag_arr = new T[bag_size];
  T* copy_ptr = x.bag_arr;

  for(unsigned int i = 0; i < this->bag_size; i++){
    this->bag_arr[i] = copy_ptr[i];
  }

  copy_ptr = nullptr;
  
  return *this;
}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  
  //bag_size++;
  if(bag_size++ > 0){
    T* temp = new T[bag_size];
    for(unsigned int i = 0; i < bag_size; i++){
      temp[i] = bag_arr[i];
    }
    delete [] bag_arr;
    //assign temp array to bag
    bag_arr = temp;
    temp = nullptr;
  } else {
    bag_arr = new T;
  }

  bag_arr[bag_size-1] = item;
  
  //return true if new item added is success
  return bag_arr[bag_size-1] == item;
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  //remove index
  unsigned int rem = 0;
  for(unsigned int i = 0; i < bag_size; i++)
  {
    if(bag_arr[i] == item){
      rem = i;
      
      T* temp = new T[bag_size-1];
      for(unsigned int j, k = 0; j < bag_size; j++){
        if(j != rem) {
          temp[k] = bag_arr[j];
          k++;
        }
      }

      delete [] bag_arr;

      bag_size--;

      bag_arr = temp;

      temp = nullptr;

      return true;
    }
  }
  return false;
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  return bag_size == 0;
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return bag_size;
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  for(unsigned int i = 0; i < bag_size; i++){
    if(bag_arr[i] == item) return true;
  }
  return false;
}

template<typename T>
void DynamicBag<T>::clear(){
  delete [] bag_arr;
  bag_arr = nullptr;
  bag_size = 0;
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  size_t freq = 0;
  for(unsigned int i = 0; i < bag_size; i++) if(bag_arr[i] == item) freq++;
  return freq;
};