#define CATCH_CONFIG_MAIN
#include "Stack.hpp"
#include "catch.hpp"

TEST_CASE("test_push") {
    Stack<int> s;
    REQUIRE(s.push(1));
    REQUIRE(s.push(2));

    REQUIRE(s.size() == 2);
}

// TEST_CASE( "test_pop" ) {
//      Stack<int> s;

//     for(unsigned i = 0; i < 100; i++) {
//         REQUIRE(s.push(i));
//         REQUIRE(s.size() == i+1);
//     }

//     REQUIRE(!s.isEmpty());

//     for(unsigned i = 100; i > 1; i--) {
//         REQUIRE(s.pop());
//         REQUIRE(s.size() == i - 1);
//     }

//     REQUIRE(s.isEmpty());
// }

TEST_CASE("clear") {
    Stack<int> s;

    for (unsigned i = 0; i < 100; i++) {
        REQUIRE(s.push(i));
        REQUIRE(s.size() == i + 1);
    }

    REQUIRE(s.peek() == 99);

    s.clear();

    REQUIRE(s.isEmpty());
    REQUIRE(s.size() == 0);
    // s.peek();

    // REQUIRE_THROWS(s.peek());

    try {
        s.peek();
    } catch (logic_error) {
        REQUIRE(s.size() == 0);
    }
}

// TEST_CASE( "size" ) {

// }

TEST_CASE("isEmpty") {
    Stack<int> s;
    REQUIRE(s.isEmpty());
    REQUIRE(s.push(100));
    REQUIRE(!s.isEmpty());
    REQUIRE(s.pop());
    REQUIRE(s.isEmpty());
}

TEST_CASE("peek") {
    Stack<int> s;
    bool success;

    try {
        s.peek();
    } catch (const std::exception& e) {
        success = true;
    }

    REQUIRE(success);

    REQUIRE(s.push(1));
    REQUIRE(s.push(2));

    REQUIRE(s.peek() == 2);
    REQUIRE(s.pop());
    REQUIRE(s.peek() == 1);
}

TEST_CASE("testing DAM stack") {
    Stack<int>* s = new Stack<int>;
    s->push(1);

    delete s;
    s = nullptr;
}