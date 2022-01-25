#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "bitset.hpp"

// THIS IS JUST AN EXAMPLE
// There should be at least one test per Bitset method

TEST_CASE( "Test bitset construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "constructors")
{
    SECTION( "Bitset(); default constructor")
    {
        Bitset b;
        REQUIRE(b.size() == 8);
        REQUIRE(b.asString() == "00000000");
        REQUIRE(b.good() == true);
        b.set(0);
        REQUIRE(b.asString() == "10000000");
        REQUIRE(b.good() == true);
        b.set(8);
        REQUIRE(b.good() == false);
    }
    SECTION( "Bitset(intmax_t size)")
    {
        SECTION("size 0")
        {
            Bitset a(0);
            REQUIRE(a.good() == false);
        }

        SECTION( "size 8" )
        {
            Bitset b(8);
            REQUIRE(b.size() == 8);
            REQUIRE(b.asString() == "00000000");
            REQUIRE(b.good() == true);
            b.set(0);
            REQUIRE(b.asString() == "10000000");
            REQUIRE(b.good() == true);
            b.set(8);
            REQUIRE(b.good() == false);
        }

        SECTION( "size 12")
        {
            Bitset c(12);
            REQUIRE(c.size() == 12);
            REQUIRE(c.asString() == "000000000000");
            REQUIRE(c.good() == true);
            c.set(0);
            REQUIRE(c.asString() == "100000000000");
            REQUIRE(c.good() == true);
            c.set(8);
            REQUIRE(c.asString() == "100000001000");
            REQUIRE(c.good() == true);
            c.set(13);
            REQUIRE(c.good() == false);
        }
    }
}