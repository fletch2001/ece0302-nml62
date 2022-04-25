#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  unsigned i = 0;

  // save item to pop
  State<T> return_state = queue[0];
  
  // pull end node to front
  queue[0] = queue[queue.size() - 1];
  queue.pop_back(); // remove previous root (in return_state)

  unsigned left;
  unsigned right;

  bool sorted = false;
  unsigned smallest = i;

  // keep sorting until sorted
  while(!sorted) {
    
    // calculate left and right child indexes
    left = 2*i + 1;
    right = 2*i + 2;
    smallest = i;

    // check left child
    if(left < queue.size() && queue[left].getFCost() < queue[smallest].getFCost()) {
      smallest = left;
    }

    // check right child
    if(right < queue.size() && queue[right].getFCost() < queue[smallest].getFCost()) {
      smallest = right;
    }

    // if smallest value is not current index, keep sorting
    if(smallest != i) {
      State<T> tmp = queue[smallest];
      queue[smallest] = queue[i];
      queue[i] = tmp;
      i++;
    } else {
      sorted = true;
    }
  }

  // return popped item
  return return_state;

}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  queue.push_back( State<T>(p, cost, heur) ); // push state to bottom of heap
  unsigned i = queue.size() - 1;
  unsigned j = i >> 1;

  while((i >= 1) && queue[j].getFCost() > queue[i].getFCost()) {
    // bubble up:
    State<T> bubble_up = queue[i]; // grab node from end to be bubbled up
    queue[i] = queue[j]; // swap parent...
    queue[j] = bubble_up;
    i = j;
    j = j >> 1; // get new parent index
  }
}

template <typename T>
bool frontier_queue<T>::empty() {
  // use vec built in function
  return (queue.size() == 0);
}

template <typename T> 
bool frontier_queue<T>::contains(const T &p) {

  for(unsigned i = 0; i < queue.size(); i++) {
    if(p == queue[i].getValue()) return true;
  }
  return false;

}

template <typename T>
void frontier_queue<T>::replaceif(const T &p, std::size_t cost) {

  // compare cost once item is found in vector
  for(unsigned i = 0; i < queue.size(); i++) {
    if(queue[i].getValue() == p) {
      if(cost < queue[i].getPathCost()) {
        queue[i].updatePathCost(cost);
        break;
      }
    }
  }
}


