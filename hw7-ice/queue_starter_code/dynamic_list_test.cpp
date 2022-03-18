#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "dynamic_array_list.h"
#include <cassert>

TEST_CASE( "constructor_getLength_isEmpty", "[getLength],[constructor],[isEmpty]" ) {
  DynamicArrayList<int> a;
  REQUIRE(a.getLength() == 0);
  REQUIRE(a.isEmpty() == 1);
}

TEST_CASE( "adding_item","[getLength], [insert]") {
    DynamicArrayList<int> a;
    a.insert(1, 1);
    REQUIRE(a.getLength() == 1);
}

TEST_CASE("adding_item_on_end") {
    DynamicArrayList<int> a;
    a.insert(1,1);
    a.insert(2,2);
    a.insert(3,3);

    REQUIRE(a.getLength() == 3);
}

TEST_CASE( "add_two_items","[getLength],[insert],[getEntry]") {
    DynamicArrayList<int> a;
    a.insert(1, 1);
    REQUIRE(a.getEntry(1) == 1);
    REQUIRE(a.getLength() == 1);
    a.insert(2, 2);
    REQUIRE(a.getEntry(2) == 2);
    REQUIRE(a.getLength() == 2);
}

TEST_CASE("adding_four_items_w_mid_insertion","[getLength],[insert],[getEntry]") {
    DynamicArrayList<int> a;
    REQUIRE(a.getLength() == 0);

    a.insert(1, 1);
    a.insert(2, 2);

    REQUIRE(a.getEntry(2) == 2);

    a.insert(3, 3);

    REQUIRE(a.getLength() == 3);
    REQUIRE(a.getEntry(3) == 3);

    a.insert(3, 4);
    REQUIRE(a.getLength() == 4);
    REQUIRE(a.getEntry(3) == 4);

    INFO(a.getEntry(3));
    REQUIRE(a.getEntry(4) == 3);
}

TEST_CASE( "removing_first_last_nodes","[getLength],[insert],[getEntry],[remove]") {
    DynamicArrayList<int> a;

    for(unsigned i = 1; i < 31; i++) {
        a.insert(i,i);
    }

    REQUIRE(a.getLength() == 30);
    REQUIRE(a.getEntry(1) == 1);
    REQUIRE(a.getEntry(30) == 30);

    SECTION( "removing tail then head") {
        a.remove(30);
        REQUIRE(a.getLength() == 29);
        
        for(unsigned i = 1; i < 30; i++) {
            REQUIRE(a.getEntry(i) == i);
        }

        REQUIRE(a.getEntry(30) == 0);

        a.remove(1);
        REQUIRE(a.getLength() == 28);

        for(unsigned i = 1; i < 29; i++) {
            REQUIRE(a.getEntry(i) == i+1);
        }
    }

    SECTION( "removing head then tail") {
        a.remove(1);
        REQUIRE(a.getLength() == 29);

        for(unsigned i = 1; i < 30; i++) {
            REQUIRE(a.getEntry(i) == i+1);
        }

        a.remove(29);
        REQUIRE(a.getLength() == 28);

        for(unsigned i = 1; i < 29; i++) {
            REQUIRE(a.getEntry(i) == i+1);
        }
    }
}

TEST_CASE( "removing_from_middle", "[getLength],[insert],[getEntry],[remove]") {
    DynamicArrayList<int> a;

    for(unsigned i = 1; i < 31; i++) {
        a.insert(i,i);
    }

    REQUIRE(a.getLength() == 30);
    REQUIRE(a.getEntry(1) == 1);
    REQUIRE(a.getEntry(30) == 30);

    a.remove(15);

    REQUIRE(a.getLength() == 29);

    for(unsigned i = 0; i < 30; i++) {
        REQUIRE(a.getEntry(i) == i + int(i/15));
    }
}

TEST_CASE( "clearing_list","[getLength],[insert],[clear]" ) {
    DynamicArrayList<int> a;

    for(unsigned i = 1; i < 61; i++) {
        a.insert(i,i);
    }

    REQUIRE(a.getLength() == 60);

    a.clear();

    REQUIRE(a.getLength() == 0);
}

TEST_CASE( "setting_item","[getLength],[insert],[setEntry]") {
    DynamicArrayList<int> a;

    for(unsigned i = 1; i < 61; i++) {
        a.insert(i,i);
    }

    REQUIRE(a.getLength() == 60);

    a.setEntry(30, 5);

    REQUIRE(a.getEntry(30) == 5);

    a.setEntry(62, 5);
    REQUIRE(a.getLength() == 60);
}

TEST_CASE( "test_equals_overload" ) {
    DynamicArrayList<int> a, b;

    for(unsigned i = 1; i < 151; i++) {
        a.insert(i, i);
    }

    b = a;

    REQUIRE(b.getLength() == a.getLength());

    for(unsigned i = 0; i < 150; i++) {
        REQUIRE(a.getEntry(i) == b.getEntry(i));
    }
}

TEST_CASE( "test_copy_constructor" ) {
    DynamicArrayList<int> a;

    for(unsigned i = 1; i < 151; i++) {
        a.insert(i, i);
    }

    DynamicArrayList<int>b(a);

    REQUIRE(b.getLength() == a.getLength());

    for(unsigned i = 0; i < 150; i++) {
        REQUIRE(a.getEntry(i) == b.getEntry(i));
    }
}