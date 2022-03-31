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

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.getEntry(i) == i);
    }

    REQUIRE_FALSE(l.remove(31));

    REQUIRE(l.remove(29));
    REQUIRE(l.getLength() == 29);
    REQUIRE(l.getEntry(29) == 30);
    
    REQUIRE(l.remove(14));
    REQUIRE(l.getEntry(28) == 30);
    REQUIRE(l.getEntry(13) == 13);
    REQUIRE(l.getEntry(14) == 15);

    unsigned j = 0;
    for(unsigned i = 1; i < 29; i++) {
        if(i == 14 || i == 28) { j++;}

        REQUIRE(l.getEntry(i) == i + j);
    }
}

TEST_CASE("testing setEntry") {
    lst l;

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.insert(i, i));
        REQUIRE(l.getEntry(i) == i);
    }

    for(unsigned i = 30; i > 0; i--) {
        l.setEntry(i, 30 - i);
    }

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.getEntry(i) == 30 - i);
    }

    for(unsigned i = 30; i > 0; i--) {
        l.setEntry(i, i);
    }

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.getEntry(i) == i);
    }
}

TEST_CASE("copy constructor") {
     lst l;

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.insert(i, i));
    }

    lst b(l);
    
    REQUIRE(b.getLength() == l.getLength());

    for(unsigned i = 1; i <= l.getLength(); i++) {
        REQUIRE(b.getEntry(i) == l.getEntry(i));
    }

    b.remove(l.getLength());

    REQUIRE_FALSE(b.getLength() == l.getLength());
    
}

TEST_CASE("copy assignment") {
     lst l;

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(l.insert(i, i));
    }

    lst b = l;
    
    REQUIRE(b.getLength() == l.getLength());

    for(unsigned i = 1; i <= l.getLength(); i++) {
        REQUIRE(b.getEntry(i) == l.getEntry(i));
    }

    l.clear();

    REQUIRE(!b.isEmpty());
}