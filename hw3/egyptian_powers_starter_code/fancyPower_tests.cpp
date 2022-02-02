#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cmath>

#include "fancyPower.hpp"

TEST_CASE("testing an even power", "fancyPower"){

  //initial tests
  REQUIRE(fancyPower(0, 2) == 1);
  REQUIRE(fancyPower(1, 2) == 2);
  REQUIRE(fancyPower(2, 2) == 4);
  REQUIRE(fancyPower(3, 2) == 8);
  REQUIRE(fancyPower(4, 2) == 16);
  REQUIRE(fancyPower(5, 2) == 32);
  
  //comprehensive tests
  for(int j = 0; j <= 10; j++){
   for(int i = 0; i <= 5; i++){
     REQUIRE(fancyPower(i, j) == std::pow(j, i));
    }
  }
}