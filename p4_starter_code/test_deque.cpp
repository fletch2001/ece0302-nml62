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

TEST_CASE("test copy assignment") {
    Deque<int>q;
    q.pushBack(1);
    q.pushBack(2);
    q.pushBack(3);
    REQUIRE(q.isEmpty() == 0);

    Deque<int>x = q;
    REQUIRE(!x.isEmpty());
    REQUIRE(x.back() == q.back());

    x.popBack();

    REQUIRE(x.front() == q.front());
    REQUIRE_FALSE(x.back() == q.back());
}

TEST_CASE("test copy constructor") {
    Deque<int>q;
    q.pushBack(1);
    q.pushBack(2);
    q.pushBack(3);
    REQUIRE(q.isEmpty() == 0);

    Deque<int>x(q);
    REQUIRE(!x.isEmpty());
    REQUIRE(x.back() == q.back());

    x.popBack();

    REQUIRE(x.front() == q.front());
    REQUIRE_FALSE(x.back() == q.back());
}