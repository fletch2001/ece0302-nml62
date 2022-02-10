#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;



TEST_CASE( "constructor_getLength_isEmpty", "[getLength],[constructor],[isEmpty]" ) {
  LinkedList<int> a;
  REQUIRE(a.getLength() == 0);
  REQUIRE(a.isEmpty() == 1);
}

TEST_CASE( "adding_item","[getLength], [insert]") {
    LinkedList<int> a;
    REQUIRE(a.insert(1, 1));
    REQUIRE(a.getLength() == 1);
}

TEST_CASE( "add_two_items","[getLength],[insert],[getEntry]") {
    LinkedList<int> a;
    REQUIRE(a.insert(1, 1));
    REQUIRE(a.getEntry(1) == 1);
    REQUIRE(a.getLength() == 1);
    REQUIRE(a.insert(2, 2));
    REQUIRE(a.getEntry(2) == 2);
    REQUIRE(a.getLength() == 2);
}

TEST_CASE("adding_four_items_w_mid_insertion","[getLength],[insert],[getEntry]") {
    LinkedList<int> a;
    REQUIRE(a.getLength() == 0);

    REQUIRE(a.insert(1, 1));
    REQUIRE(a.insert(2, 2));

    REQUIRE(a.getEntry(2) == 2);

    REQUIRE(a.insert(3, 3));

    REQUIRE(a.getLength() == 3);
    REQUIRE(a.getEntry(3) == 3);

    REQUIRE(a.insert(3, 4));
    REQUIRE(a.getLength() == 4);
    REQUIRE(a.getEntry(3) == 4);
    REQUIRE(a.getEntry(4) == 3);
}

TEST_CASE( "removing_first_last_nodes","[getLength],[insert],[getEntry],[remove]") {
    LinkedList<int> a;

    for(unsigned i = 1; i < 31; i++) {
        REQUIRE(a.insert(i,i));
    }

    REQUIRE(a.getLength() == 30);
    REQUIRE(a.getEntry(1) == 1);
    REQUIRE(a.getEntry(30) == 30);

    SECTION( "removing tail then head") {
        REQUIRE(a.remove(30) == 1);
        REQUIRE(a.getLength() == 29);
        
        for(unsigned i = 1; i < 30; i++) {
            REQUIRE(a.getEntry(i) == i);
        }

        REQUIRE(a.getEntry(30) == 0);

        REQUIRE(a.remove(1) == 1);
        REQUIRE(a.getLength() == 28);

        for(unsigned i = 1; i < 29; i++) {
            REQUIRE(a.getEntry(i) == i+1);
        }
    }

    SECTION( "removing head then tail") {
        REQUIRE(a.remove(1) == 1);
        REQUIRE(a.getLength() == 29);

        for(unsigned i = 1; i < 30; i++) {
            REQUIRE(a.getEntry(i) == i+1);
        }

        REQUIRE(a.remove(29) == 1);
        REQUIRE(a.getLength() == 28);

        for(unsigned i = 1; i < 29; i++) {
            REQUIRE(a.getEntry(i) == i+1);
        }
    }
}