#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"
#include "priority_queue.h"

TEST_CASE("Testing Priority Queue", "[priority queue]") {
  typedef SortedList<int, DynamicArrayList<int> > SortedListType;
  typedef PriorityQueue<int, SortedListType>  PriorityQueueType;

  PriorityQueueType pq;

  pq.add(0);
  pq.add(2);
  pq.add(1);
  REQUIRE(pq.peek() == 2);
  pq.remove();
  REQUIRE(pq.peek() == 1);
  
  pq.add(7);
  REQUIRE(pq.peek() == 7);

  pq.add(6);
  REQUIRE(pq.peek() == 7);

  REQUIRE(pq.isEmpty() == 0);

  pq.remove();
  
  REQUIRE(pq.peek() == 6);

  pq.remove();
  REQUIRE(pq.peek() == 1);

  pq.remove();
  pq.remove();
  REQUIRE(pq.isEmpty());

}
