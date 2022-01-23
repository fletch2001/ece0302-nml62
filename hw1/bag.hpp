#ifndef STUDENT_BAG_HPP
#define STUDENT_BAG_HPP

#include <cstdlib>

template<typename T> class Bag{
public:

  Bag();
  
  Bag(const Bag<T> &) = delete;

  const Bag<T> operator=(const Bag<T> &) = delete;

  ~Bag();

  std::size_t getCurrentSize() const;

  bool isEmpty() const;

  bool add(const T& entry);

  bool remove(const T& entry);

  void clear();

  std::size_t getFrequencyOf(const T& entry) const;

  bool contains(const T& entry) const;

private:
  T* items; //array of items
  unsigned int bagSize;
  unsigned int maxSize;
  unsigned int max_size_increment;
};

#include "bag.tpp"

#endif
