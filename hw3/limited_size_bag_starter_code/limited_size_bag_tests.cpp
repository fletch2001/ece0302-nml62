#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE( "test add" ) {
  LimitedSizeBag<int> a;
  REQUIRE(a.add(0) == 1);
  REQUIRE(a.add(1) == 1);

  for(unsigned i = 0; i <= 17; i++) {
    REQUIRE(a.add(i));
  }

  REQUIRE(a.getCurrentSize() == 20);

  REQUIRE(!a.add(12));

}

TEST_CASE( "test getCurrentSize" ) {
  LimitedSizeBag<int> a;
  for(unsigned i = 0; i < 20; i++) {
    a.add(i);
    REQUIRE(a.getCurrentSize() == i+1);
  }
  REQUIRE(a.getCurrentSize() == 20);

  a.add(20);
  REQUIRE(a.getCurrentSize() == 20);

}

TEST_CASE( "test getFrequency" ) {
  LimitedSizeBag<int> a;
  for(unsigned i = 0; i < 10; i++) {
    REQUIRE(a.add(i));
    REQUIRE(a.add(i));
  }

  REQUIRE(a.getCurrentSize() == 20);

  for(unsigned i = 0; i < 10; i++) {
    REQUIRE(a.getFrequencyOf(i) == 2);
  }

}

TEST_CASE( "test remove") {
  LimitedSizeBag<int> a;

  SECTION( "testing two of one item" ) {
    REQUIRE(a.add(3));
    REQUIRE(a.add(3));

    REQUIRE(a.getFrequencyOf(3) == 2);

    REQUIRE(a.remove(3));
    REQUIRE(a.getFrequencyOf(3));
  }

  SECTION( "testing more than 2" ) {
    for(unsigned i = 0; i < 10; i++) {
      REQUIRE(a.add(i));
      REQUIRE(a.add(i));
    }

    REQUIRE(a.getFrequencyOf(0) == 2);
    REQUIRE(a.getCurrentSize() == 20);

    for(unsigned i = 0; i < 10; i++) {

      REQUIRE(a.remove(i));

      REQUIRE(a.getFrequencyOf(i) == 1);
      REQUIRE(a.getCurrentSize() == 20 - 1 - i);
    }
  }
}

TEST_CASE( "test clear" ) {
  LimitedSizeBag<int> a;
  for(unsigned i = 0; i < 10; i++) {
    REQUIRE(a.add(i));
    REQUIRE(a.add(i));
  }
  a.clear();

  REQUIRE(a.getCurrentSize() == 0);
}

TEST_CASE( "test isEmpty") {
  LimitedSizeBag<int> a;
  SECTION( "testing by adding them removing" ) {
    for(unsigned i = 0; i < 10; i++) {
      REQUIRE(a.add(i));
      REQUIRE(a.add(i));
    }

    REQUIRE( !a.isEmpty() );

    for(unsigned i = 0; i < 10; i++) {
      REQUIRE(a.remove(i));
      REQUIRE(a.remove(i));
    }

    REQUIRE( a.isEmpty() );

  }

  SECTION( "testing by adding then clearing" ) {
    for(unsigned i = 0; i < 10; i++) {
      REQUIRE(a.add(i));
      REQUIRE(a.add(i));
    }

    REQUIRE( !a.isEmpty() );

    a.clear();

    REQUIRE( a.isEmpty() );

  }

}

TEST_CASE( "test constructor") {
  LimitedSizeBag<int> a;
  REQUIRE(a.getCurrentSize() == 0);
}

TEST_CASE( "copy constructor" ) {
  LimitedSizeBag<int> a;
  for(unsigned i = 0; i < 20; i++) {
    REQUIRE(a.add(i) == 1);
  }

  REQUIRE(a.getCurrentSize() == 20);

  LimitedSizeBag<int> b(a);
  REQUIRE(b.getCurrentSize() == 20);

  REQUIRE(b.remove(5));

  REQUIRE(a.contains(5));
  REQUIRE(a.getCurrentSize() == 20);

}

TEST_CASE( "= operator" ) {
  LimitedSizeBag<int> a;
  for(unsigned i = 0; i < 10; i++) {
    REQUIRE(a.add(i));
    REQUIRE(a.add(i));
  }

  LimitedSizeBag<int> b;

  b = a;
  REQUIRE(b.getCurrentSize() == a.getCurrentSize());
  for(unsigned i = 0; i < 10; i++) {
    REQUIRE(b.contains(i));
    REQUIRE(b.getFrequencyOf(i) == 2);
  }

}