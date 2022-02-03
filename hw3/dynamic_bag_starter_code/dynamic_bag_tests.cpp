#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  REQUIRE(b.getFrequencyOf(0) == 0);
  b.contains(0);
}

TEST_CASE( "adding then using copy constructor" ) {
  DynamicBag<int> a;

  a.add(5);
  a.add(6);
  REQUIRE(a.getCurrentSize() == 2);

  DynamicBag<int> b(a);
  REQUIRE(b.getCurrentSize() == 2);
  REQUIRE(b.contains(6) == 1);
  b.remove(6);
  REQUIRE(b.contains(6) == 0);
  REQUIRE(a.contains(6) == 1);

  REQUIRE(a.getCurrentSize() == 2);
  REQUIRE(b.getCurrentSize() == 1);

} 

TEST_CASE( "adding 3 items" ) {
  DynamicBag<int> a;
  REQUIRE(a.add(0));
  REQUIRE(a.contains(0));
  REQUIRE(a.getCurrentSize() == 1);
  
  REQUIRE(a.add(1));
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(0));
  REQUIRE(a.getCurrentSize() == 2);

  REQUIRE(a.add(2));
  REQUIRE(a.contains(2));
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(0));
  REQUIRE(a.getCurrentSize() == 3);
}

TEST_CASE( "adding then using equals operator" ) {
  DynamicBag<int> a;

  a.add(5);
  a.add(6);
  REQUIRE(a.getCurrentSize() == 2);

  DynamicBag<int> b;
  b = a;
  REQUIRE(b.getCurrentSize() == 2);
  REQUIRE(b.contains(6) == 1);
  b.remove(6);
  REQUIRE(b.contains(6) == 0);
  REQUIRE(a.contains(6) == 1);
  
  REQUIRE(a.getCurrentSize() == 2);
  REQUIRE(b.getCurrentSize() == 1);
} 

TEST_CASE( "adding 41 items" ){
  DynamicBag<int> a;
  for(int i = 0; i < 41; i++) {
    REQUIRE(a.add(i));
    REQUIRE(a.getCurrentSize() == i+1);
    REQUIRE(a.contains(i));
    REQUIRE(!a.isEmpty());
  }

  REQUIRE(a.contains(0));
  REQUIRE(a.contains(1));
  REQUIRE(a.contains(2));

  //testing copying
  DynamicBag<int> b(a);
  DynamicBag<int> c;
  c = a;
  
  REQUIRE(b.getCurrentSize() == 41);
  REQUIRE(c.getCurrentSize() == 41);
  REQUIRE(b.contains(40));

  SECTION( "testing copy constructed bag" ) {

    for(int i = 40; i >= 0; i--) {
      REQUIRE(b.contains(i));
      REQUIRE(!b.isEmpty());
    }
  }

  SECTION ( "testing equals assigned bag" ) {

    for(int i = 40; i >= 0; i--) {
      REQUIRE(c.contains(i));
      REQUIRE(!c.isEmpty());
    }
  }
}