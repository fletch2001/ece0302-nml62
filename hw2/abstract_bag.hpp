#ifndef _ABSTRACT_BAG_HPP
#define _ABSTRACT_BAG_HPP

template<typename T> class abstract_bag{
public:

  //gets current size
  virtual std::size_t getCurrentSize() const = 0;

  //returns if empty or not
  virtual bool isEmpty() const = 0;

  //adds entry to bag
  virtual bool add(const T& entry) = 0;

  //removes instance of entry from bag
  virtual bool remove(const T& entry) = 0;

  //clears bag
  virtual void clear() = 0;

  //gets frequency of items occurring in bag
  virtual std::size_t getFrequencyOf(const T& entry) const = 0;

  //returns whether bag contains at least one instance of an item or not
  virtual bool contains(const T& entry) const = 0;

};

#endif