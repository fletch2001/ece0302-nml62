#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include "sorted_list.h"

TEST_CASE("Testing Sorted List", "[sorted list]") {
  typedef SortedList<int, DynamicArrayList<int> > slst;
  
  slst lst;

  lst.insert(1);
  lst.insert(2);

  REQUIRE(lst.getLength() == 2);
  REQUIRE(lst.getEntry(0) == 1);
  REQUIRE(lst.getEntry(1) == 2);

  REQUIRE(lst.getPosition(1) == 0);
  REQUIRE(lst.getPosition(2) == 1);
  REQUIRE(lst.getPosition(3) == -2);
  REQUIRE(lst.getPosition(4) == -2);
  lst.insert(4);
  REQUIRE(lst.getPosition(4) == 2);
  REQUIRE(lst.getEntry(2) == 4);

  REQUIRE(lst.getPosition(3) == -2);

  lst.remove(2);
  REQUIRE(lst.getLength() == 2);
  REQUIRE(lst.getEntry(0) == 1);
  REQUIRE(lst.getEntry(1) == 4);
  REQUIRE(lst.getPosition(1) == 0);
  REQUIRE(lst.getPosition(2) == -1);
  REQUIRE(lst.getPosition(4) == 1);

  lst.insert(2);

  REQUIRE(lst.getPosition(4) == 2);
  REQUIRE(lst.getPosition(3) == -2);

  lst.insert(3);
  REQUIRE(lst.getPosition(3) == 2);
  REQUIRE(lst.getPosition(4) == 3);

  REQUIRE(lst.getPosition(5) == -4);

}

typedef SortedList<char, DynamicArrayList<int> > ListType;
TEST_CASE("Testing isEmpty", "[sorted list]") {
  ListType lst;
  REQUIRE(lst.isEmpty());

  lst.insert('a');
  REQUIRE(!lst.isEmpty());

  lst.removeAt(0);
  REQUIRE(lst.isEmpty());
}

TEST_CASE("Testing getLength", "[sorted list]") {
  ListType lst;
  REQUIRE(lst.getLength() == 0);

  lst.insert('b');
  REQUIRE(lst.getLength() == 1);

  lst.insert('a');
  REQUIRE(lst.getLength() == 2);

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 1);

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 0);
}

TEST_CASE("Testing insert", "[sorted list]") {
  ListType lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  for (int i = 0; i < 26; ++i) {
    REQUIRE(lst.getEntry(i) == 'a' + i);
  }
}

TEST_CASE("Testing remove", "[sorted list]") {
  ListType lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  lst.removeAt(5);
  REQUIRE(lst.getLength() == 25);
  REQUIRE(lst.getEntry(5) == 'g');

  lst.removeAt(11);
  REQUIRE(lst.getLength() == 24);
  REQUIRE(lst.getEntry(11) == 'n');

  lst.removeAt(0);
  REQUIRE(lst.getLength() == 23);
  REQUIRE(lst.getEntry(0) == 'b');

  lst.removeAt(22);
  REQUIRE(lst.getLength() == 22);
  REQUIRE(lst.getEntry(21) == 'y');
}

TEST_CASE("Testing clear", "[sorted list]") {
  ListType lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  lst.clear();
  REQUIRE(lst.getLength() == 0);

  c = 'a';
  while (c <= 'j') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 10);

  ListType lst_empty;
  lst_empty.clear();
  REQUIRE(lst_empty.getLength() == 0);
}

TEST_CASE("Testing getEntry", "[sorted list]") {
  ListType lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  for (int i = 0; i < 26; ++i) {
    REQUIRE(lst.getEntry(i) == 'a' + i);
  }
}

TEST_CASE("Testing copy", "[sorted list]") {
  ListType lst;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  ListType lst_copy = lst;

  REQUIRE(lst_copy.getLength() == 26);

  for (int i = 0; i < 26; ++i) {
    REQUIRE(lst_copy.getEntry(i) == lst.getEntry(i));
  }
}

TEST_CASE("Testing copy empty", "[sorted list]") {
  ListType lst;
  ListType lst_copy = lst;

  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst_copy.getLength() == 0);
}

TEST_CASE("Testing assignment", "[sorted list]") {
  ListType lst;
  ListType lst_copy;

  char c = 'a';
  while (c <= 'z') {
    lst.insert(c);
    ++c;
  }
  REQUIRE(lst.getLength() == 26);

  lst_copy = lst;

  REQUIRE(lst_copy.getLength() == 26);

  for (int i = 0; i < 26; ++i) {
    REQUIRE(lst_copy.getEntry(i) == lst.getEntry(i));
  }
}

TEST_CASE("Testing assignment to/from empty", "[sorted list]") {
  ListType lst;
  ListType lst_copy;

  lst_copy = lst;

  REQUIRE(lst.getLength() == 0);
  REQUIRE(lst_copy.getLength() == 0);
}

TEST_CASE("Testing exceptions", "[sorted list]") {
  ListType lst;

  CHECK_THROWS_AS(lst.removeAt(0), std::range_error);
  CHECK_THROWS_AS(lst.getEntry(0), std::range_error);

  lst.insert('a');
  lst.insert('b');
  lst.insert('c');
  lst.insert('d');

  CHECK_THROWS_AS(lst.removeAt(4), std::range_error);
  CHECK_THROWS_AS(lst.removeAt(5), std::range_error);
  CHECK_THROWS_AS(lst.getEntry(4), std::range_error);
  CHECK_THROWS_AS(lst.getEntry(5), std::range_error);

  CHECK_THROWS_AS(lst.removeAt(-1), std::range_error);
  CHECK_THROWS_AS(lst.getEntry(-1), std::range_error);
}

TEST_CASE("Testing getPosition") {
  ListType lst;

  lst.insert('a');
  lst.insert('b');

  REQUIRE(lst.getPosition('c') == -2);

  lst.insert('c');

  REQUIRE(lst.getPosition('e') == -3);
  lst.insert('e');
  
  REQUIRE(lst.getPosition('d') == -3);
  lst.insert('d');
  
  REQUIRE(lst.getPosition('d') == 3);
  REQUIRE(lst.getPosition('e') == 4);
  REQUIRE(lst.getPosition('a') == 0);
  REQUIRE(lst.getPosition('z') == -5);

  lst.insert('a');
  REQUIRE(lst.getPosition('a') == 0);
  REQUIRE(lst.getPosition('b') == 2);
}
