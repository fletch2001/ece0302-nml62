#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "add.hpp"

// force template expansion
template class Add<int>;

TEST_CASE("Test add", "[Add]"){

  Add<int> a;
  REQUIRE(a.call(1,2)==3);
  REQUIRE(a.call(2,2)==4);
  REQUIRE(a.call(2.5, 2.5)==4);
  REQUIRE(a.call(10,11)==21);
}
