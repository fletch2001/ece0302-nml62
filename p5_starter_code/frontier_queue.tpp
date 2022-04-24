#include "frontier_queue.hpp"

// TODO implement the member functions here

template <typename T>
State<T> frontier_queue<T>::pop() {
  unsigned i = 0;
  // if(queue.size() > 4) {
  // std::cout << "      " << queue[i].getFCost() << "\n";
  // std::cout << "   " << queue[2 * i + 1].getFCost() << "    " << queue[2 * i + 2].getFCost() << "\n";
  // std::cout << queue[2 * (2 * i + 1) + 1].getFCost() << "    " << queue[2 * (2 * i + 1) + 2].getFCost() << "\n\n";
  // } 

  std::cout << "PRE_POP\n\n";
  for(unsigned i = 0; i < queue.size(); i++) {
    std::cout << queue[i].getFCost() << " ";
  }

  std::cout << "\n\n\n";

  State<T> return_state = queue[0];
  queue[0] = queue[queue.size() - 1];
  queue.pop_back(); // remove previous root (in return_state)

  while(i < queue.size()) {
    if(queue[i].getFCost() > queue[(2*i) + 1].getFCost() || queue[i].getFCost() > queue[(2*i) + 2].getFCost()) {
      if(queue[(2*i) + 1].getFCost() < queue[(2*i) + 2].getFCost()) {
        State<T> tmp = queue[i];
        queue[i] = queue[(2*i) + 1];
        queue[(2*i) + 1] = tmp;
        i = (2*i) + 1; // follow max item to left child branch
      } else {
        State<T> tmp = queue[i];
        queue[i] = queue[(2*i) + 2];
        queue[(2*i) + 2] = tmp;
        i = (2*i) + 2; // follow max item to right child branch
      } 
    } else break;
  }

  std::cout << "POST_POP\n\n";
  for(unsigned i = 0; i < queue.size(); i++) {
    std::cout << queue[i].getFCost() << " ";
  }

  std::cout << "\n\n\n";

  return return_state;
  // State<T> return_item = queue[0];
  // queue[0] = queue[queue.size() - 1] ; // move last node up to top of queue
  // queue.pop_back(); // remove deleted node (originally root)
  // //queue[queue.size() - 1] = return_item;

  // std::cout << "PRE_POP\n\n";
  // for(unsigned i = 0; i < queue.size(); i++) {
  //   std::cout << queue[i].getFCost() << " ";
  // }

  // std::cout << "\n\n\n";

  // unsigned i = 0;

  // while(i < queue.size()) {
  //   if(queue[2*i].getFCost() < queue[2*i + 1].getFCost()) { // l is smaller than r -> test left and parent 
  //     if(queue[i].getFCost() > queue[2*i].getFCost()) {
  //       State<T> tmp = queue[i];
  //       queue[i] = queue[2*i];
  //       queue[2*i] = tmp;
  //        if(queue[(2*i) + 1] != 0) {
  //           i = (2 * i) + 1;  
  //       } else {
  //       return return_item;
  //     }
  //   } else { // r is smaller than r -> test r and parent
  //     if(queue[i].getFCost() > queue[2*i + 1].getFCost()) {
  //       State<T> tmp = queue[i];
  //       queue[i] = queue[2*i + 1];
  //       queue[2*i + 1] = tmp;
  //       if(queue[(2*i) + 2] != 0) {
  //           i = (2 * i) + 2;  
  //       } else {
  //       return return_item;
  //     }
  //   }
  // }

  // return return_item;
  //TODO
  
  //implement this the same way we implemented pop in the heap lecture. Compare using getFCost

  // needs return statement

}

template <typename T>
void frontier_queue<T>::push(const T &p, std::size_t cost, std::size_t heur) {

  queue.push_back( State<T>(p, cost, heur) ); // push state to bottom of heap
  unsigned i = queue.size() - 1;
  unsigned j = i >> 1;

  // for(unsigned k = 0; k < queue.size(); k++) {
  //   std::cout << queue[k].getFCost() << " ";
  // }

  // std::cout << "\n\n";

  while((i >= 1) && queue[j].getFCost() > queue[i].getFCost()) {
    // bubble up:
    State<T> bubble_up = queue[i]; // grab node from end to be bubbled up
    queue[i] = queue[j]; // swap parent...
    queue[j] = bubble_up;
    i = j;
    j = j >> 1; // get new parent index
  }

  for(unsigned i = 0; i < queue.size(); i++) {
    std::cout << queue[i].getFCost() << " ";
  }

  std::cout << "\n\n\n\n";

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

  //TODO

}


