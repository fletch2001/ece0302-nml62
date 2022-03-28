#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "linked_list.hpp"

typedef LinkedList<int> lst;

TEST_CASE("insert") {
    lst l;
    REQUIRE(l.insert(0, 1) == 0);
    REQUIRE(l.insert(2, 1) == 0);

    REQUIRE(l.insert(1, 1));
    REQUIRE(l.getEntry(1) == 1);
    REQUIRE(l.getLength() == 1);

    REQUIRE(l.insert(2, 2));
    REQUIRE(l.getEntry(1) == 1);
    REQUIRE(l.getEntry(2) == 2);
    REQUIRE(l.getLength() == 2);

    REQUIRE(l.insert(2, -1));
    REQUIRE(l.getEntry(2) == -1);
    REQUIRE(l.getEntry(3) == 2);
    REQUIRE(l.getLength() == 3);
}

TEST_CASE("remove") {
    lst l;

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.insert(i, i));
        REQUIRE(l.getEntry(i) == i);
    }

    REQUIRE(l.getLength() == 30);

    REQUIRE(l.getEntry(5) == 5);
    REQUIRE(l.remove(5));
    REQUIRE(l.getEntry(5) == 6);
    REQUIRE(l.getLength() == 29);

    REQUIRE(l.insert(5, 5));
    REQUIRE(l.getEntry(5) == 5);
    REQUIRE(l.getEntry(6) == 6);
    REQUIRE(l.getLength() == 30);
    

    REQUIRE(l.remove(1));
    REQUIRE(l.getLength() == 29);
    REQUIRE(l.getEntry(1) == 2);
    REQUIRE(l.insert(1, 1));
    REQUIRE(l.getEntry(1) == 1);

    REQUIRE_FALSE(l.remove(31));

}