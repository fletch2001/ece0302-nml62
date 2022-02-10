#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "test constructor", "[ArrayList]" ) {
  ArrayList<int> l;

  REQUIRE(l.getLength() == 0);
}

TEST_CASE( "test copy constructor" ) {
  ArrayList<int> l;
  REQUIRE(l.getLength() == 0);
  
  for(unsigned i = 1; i < 40; i++) {
    REQUIRE(l.insert(i, i));
  }

  ArrayList<int> c(l);

  for(unsigned i = 1; i < 40; i++) {
    REQUIRE(c.getEntry(i) == l.getEntry(i)); 
  }

}

TEST_CASE("test insert") {
  ArrayList<int> l;
  REQUIRE(l.insert(1,5));
  REQUIRE(!l.insert(3,5));
  REQUIRE(!l.insert(0,4));
  REQUIRE(l.insert(2, 4));
}

TEST_CASE( "test =") {
  ArrayList<int> l, c;
  REQUIRE(l.getLength() == 0);
  
  for(unsigned i = 1; i < 40; i++) {
    REQUIRE(l.insert(i, i));
  }
  
  c = l;

  for(unsigned i = 1; i < 40; i++) {
    REQUIRE(c.getEntry(i) == l.getEntry(i)); 
  }
}

TEST_CASE( "test isEmpty" ) { 
  ArrayList<int> l;
  REQUIRE(l.isEmpty());

  REQUIRE(l.insert(1, 5));
  REQUIRE(!l.isEmpty());
}

TEST_CASE( "getLength" ) { 
  ArrayList<int> l;
  REQUIRE(l.getLength() == 0);
  REQUIRE(l.insert(1, 0));
  REQUIRE(l.getLength() == 1);

  for(unsigned i = 2; i < 40; i++) {
    REQUIRE(l.insert(i,i));
    REQUIRE(l.getLength() == i);
  }
}

TEST_CASE( "test remove" ) { 
  ArrayList<int> l;
  REQUIRE(l.insert(1, 1));
  REQUIRE(l.insert(2, 2));
  REQUIRE(l.insert(3, 3));
  REQUIRE(l.getLength() == 3);

  REQUIRE(l.remove(2));
  REQUIRE(!l.remove(3));

  REQUIRE(l.getLength() == 2);
  REQUIRE(l.getEntry(2) == 3);
}

TEST_CASE( "test getEntry" ) { 
  ArrayList<int> l;
  for(unsigned i = 1; i < 40; i++) {
    REQUIRE(l.insert(i,i));
  }

  for(unsigned i = 39; i > 0; i--) {
    REQUIRE(l.getEntry(i) == i);
  }
}

TEST_CASE( "setEntry" ) { 
  ArrayList<int> l;
  for(unsigned i = 1; i < 40; i++)
    REQUIRE(l.insert(i, i));
  
  REQUIRE(l.getLength() == 39);
  REQUIRE(l.getEntry(34) == 34);

  l.setEntry(34, 5);
  REQUIRE(l.getLength() == 39);

  REQUIRE(l.getEntry(34) == 5);
}

TEST_CASE( "test clear" ) { 
  ArrayList<int> l;

  for(unsigned i = 1; i < 40; i++)
    REQUIRE(l.insert(i, i));

  REQUIRE(l.getLength() == 39);

  l.clear();

  REQUIRE(l.getLength() == 0);
}