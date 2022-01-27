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

        SECTION( "size 1")
        {
            Bitset a(1);
            REQUIRE(a.size() == 1);
            REQUIRE(a.asString() == "0");
            a.toggle(0);
            REQUIRE(a.asString() == "1");
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

//testing that size function properly returns for variety of sizes
TEST_CASE( ".size()" ){
    Bitset b(1);
    Bitset a(2);
    Bitset f(100);

    REQUIRE(b.size() == 1);
    REQUIRE(a.size() == 2);
    REQUIRE(f.size() == 100);
}

//testing bitset validity
TEST_CASE( ".good()"){
    Bitset a(0);
    REQUIRE(a.good() == false);

    Bitset b( 12 );
    REQUIRE(b.good() == true);
    for(int i = 0; i < b.size(); i++){
        b.toggle(i);
        SECTION("good after toggle(0≤i≤N-1)")
            REQUIRE(b.good() == true);
        b.set(i);
        SECTION("good after set(0≤i≤N-1)")
            REQUIRE(b.good() == true);
        b.reset(i);
        SECTION("good after reset(0≤i≤N-1)")
            REQUIRE(b.good() == true);
    }
}

//testing set
TEST_CASE(".set()"){
    Bitset a(12);

    std::string bits;

    for(int i = 0; i < a.size(); i++) bits += "0";

    REQUIRE(a.asString() == bits);

    for(int i = 0; i < a.size(); i++){
        a.set(i);
        bits[i] = '1';
        REQUIRE(a.asString() == bits);
    }

    a.set(a.size());

    REQUIRE(!a.good());
}

//testing reset
TEST_CASE( ".reset()" ){
    Bitset a(12);

    std::string bits;

    for(int i = 0; i < a.size(); i++){
        bits += "1";
        a.toggle(i);
    }

    REQUIRE(a.asString() == bits);

    for(int i = 0; i < a.size(); i++){
        a.reset(i);
        bits[i] = '0';
        REQUIRE(a.asString() == bits);
    }

    a.reset(a.size());

    REQUIRE(!a.good());
}

//testing test
TEST_CASE( ".test()" ){
    Bitset a(12);

    for(int i = 0; i < a.size(); i++)
    {
        REQUIRE(a.test(i) == false);

        a.toggle(i);

        REQUIRE(a.test(i) == true);
    }
    REQUIRE(a.test(a.size()-1));
    REQUIRE(!a.test(a.size()));
}

//testing bitstrings
TEST_CASE("bit strings"){
    unsigned int max_string_size = 256;
    std::string bitString(max_string_size, '0');

    //REQUIRE(bitString == "00000000"); //just to check initial bitstring

    //Bitset b(8);

    for(int i = 0; i < max_string_size; i++)
    {
        int mask[] = {(i >> 0) % 2, (i >> 1) % 2, (i >> 2) % 2, (i >> 3) % 2, (i >> 4) % 2, (i >> 5) % 2, (i >> 6) % 2, (i >> 7) % 2};
        //bitString = std::to_string((i >> 7) % 2) + std::to_string((i >> 6) % 2) + std::to_string((i >> 5) % 2) + std::to_string((i >> 4) % 2) + std::to_string((i >> 3) % 2) + std::to_string((i >> 2) % 2) + std::to_string((i >> 1)% 2) + std::to_string(i % 2);
        bitString = std::to_string(mask[7]) + std::to_string(mask[6]) + std::to_string(mask[5]) + std::to_string(mask[4]) + std::to_string(mask[3]) + std::to_string(mask[2]) + std::to_string(mask[1]) + std::to_string(mask[0]);
        Bitset b(bitString);
        // SECTION("using toggle to set bits")
        // {
        //     if(mask[0])
        // }
        REQUIRE(bitString == b.asString());
        //std::cout << i << " " << bitString << std::endl;
        //REQUIRE()
    }

}