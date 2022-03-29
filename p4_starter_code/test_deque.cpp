#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

typedef Deque<int> dq;

TEST_CASE( "test deque", "[deque]" ) {
    dq q;

    REQUIRE(q.isEmpty());

    q.pushFront(1);
    REQUIRE(q.front() == 1);
    REQUIRE(q.back() == 1);
    
    q.pushFront(2);
    q.pushBack(2);
    
    REQUIRE(q.front() == 2);
    REQUIRE(q.back() == 2);
    
    q.popFront();
    REQUIRE(q.front() == 1);
    REQUIRE(q.back() == 2);

    q.pushBack(3);
    REQUIRE(q.front() == 1);
    REQUIRE(q.back() == 3);

    q.popBack();
    REQUIRE(q.back() == 2);
    REQUIRE(q.front() == 1);

    q.popBack();
    REQUIRE(q.back() == 1);
    REQUIRE(q.front() == 1);

    q.popFront();
    REQUIRE_THROWS(q.popBack());
    REQUIRE_THROWS(q.popFront());

    REQUIRE(q.isEmpty());

}
