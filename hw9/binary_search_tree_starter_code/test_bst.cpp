#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "binary_search_tree.h"

typedef BinarySearchTree<int, int> TreeType;

TEST_CASE("Test Construction", "[construction]") {
    TreeType bst1;

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("Test Insert", "[insert]") {
    TreeType bst1;

    bst1.insert(10, 10);
    REQUIRE(!bst1.isEmpty());
}

TEST_CASE("Test Duplicate Insert", "[duplicate insert]") {
    TreeType bst1;
    
    bst1.insert(12, 12);
    REQUIRE(!bst1.insert(12, 12));
}

TEST_CASE("Test Retrieve", "[retrieve]") {
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;
    REQUIRE(bst1.retrieve(18, item));
    REQUIRE(bst1.retrieve(12, item));
    REQUIRE(bst1.retrieve(15, item));
    REQUIRE(bst1.retrieve(5, item));
    REQUIRE(bst1.retrieve(10, item));
}

TEST_CASE("Test Remove", "[remove]") {
    TreeType bst1;

    bst1.insert(10, 10);
    bst1.insert(5, 5);
    bst1.insert(15, 15);
    bst1.insert(12, 12);
    bst1.insert(18, 18);

    int item;

    bst1.remove(12);
    REQUIRE(!bst1.retrieve(12, item));

    bst1.remove(18);
    REQUIRE(!bst1.retrieve(18, item));

    bst1.remove(5);
    REQUIRE(!bst1.retrieve(5, item));

    bst1.remove(10);
    REQUIRE(!bst1.retrieve(10, item));

    bst1.remove(15);
    REQUIRE(!bst1.retrieve(15, item));

    REQUIRE(bst1.isEmpty());
}

TEST_CASE("Test Copy Assign", "[copy assign]") {
    TreeType bst1;

    bst1.insert(50, 50);
    bst1.insert(0, 0);
    bst1.insert(100, 100);
    bst1.insert(25, 25);
    bst1.insert(75, 75);

    TreeType bst2;

    bst2 = bst1;

    REQUIRE(!bst2.isEmpty());

    int item;
    REQUIRE(bst2.retrieve(100, item));
    REQUIRE(bst2.retrieve(75, item));
    REQUIRE(bst2.retrieve(50, item));
    REQUIRE(bst2.retrieve(25, item));
    REQUIRE(!bst2.retrieve(51, item));
    
}

TEST_CASE("test treesort") {
    TreeType bst1;
    int arr[] = {3, 2, 6, 7};
    bst1.treeSort(arr, 4);
    REQUIRE(arr[0] == 2);
    REQUIRE(arr[1] == 3);
    REQUIRE(arr[2] == 6);
    REQUIRE(arr[3] == 7);

    int arr_b[] {3, 4, 1, 3};
    bst1.treeSort(arr_b, 4);
    REQUIRE(arr_b[0] == 3);
    REQUIRE(arr_b[1] == 4);
    REQUIRE(arr_b[2] == 1);
    REQUIRE(arr_b[3] == 3);

    bst1.remove(3);
    bst1.remove(2);
    bst1.remove(6);
    bst1.remove(7);

    REQUIRE(bst1.isEmpty());

    int arr_c[] = {5, 4, 6, 2, 3, 9, 0, 1};
    bst1.treeSort(arr_c, 8);
    REQUIRE(arr_c[0] == 0);
    REQUIRE(arr_c[7] == 9);
}