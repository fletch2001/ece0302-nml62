#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bag.hpp"

// force template expansion
template class Bag<int>;

TEST_CASE(".add(entry)","[bag]")
{
  Bag<int> b;
  SECTION("0<=bagSize<=maxSize")
  {
    for(int i = 0; i < 10; i++)
    {
      SECTION("b.add( i = " + std::to_string(i) + " )")
      {
        REQUIRE(b.add(i)==true);
      }
    }
  }
  
  SECTION("maxSize <bagSize <= 3*maxSize")
  {
    for(int i = 10; i < 31; i++)
    {
      SECTION("b.add(i = " + std::to_string(i) + ")")
      {
        REQUIRE(b.add(i)==1);
      }
    }
  }
}

TEST_CASE(".remove(entry)","[bag]")
{
  Bag<int> b;
  SECTION("add items")
  {
    for(int i = 0; i < 31; i++)
    {
      REQUIRE(b.add(i)==1);
    }
    
    REQUIRE(b.contains(0)==1);
    REQUIRE(b.contains(30)==1);
  }

  for(int i = 30; i >= 0; i--)
  {
    REQUIRE(b.remove(i)==1);
  }
  REQUIRE(b.isEmpty()==1);
}

TEST_CASE(".getFrequency()","[bag]")
{
  Bag<int> b;
  for(int i = 0; i < 11; i++)
  {
    for(int j = 0; j < i; j++)
    {
      b.add(i);
    }
    REQUIRE(b.getFrequencyOf(i)==i);
  }
}

TEST_CASE(".clear()","[bag]")
{
  Bag<int> b;
  for(int i = 0; i < 20; i++)
  {
    b.add(i);
  }
  REQUIRE(b.isEmpty()==0);
  REQUIRE(b.getCurrentSize()==20);
  b.clear();
  REQUIRE(b.isEmpty()==1);
  REQUIRE(b.getCurrentSize()==0);
}

TEST_CASE("adding then clearing and adding over maxSize items", "[bag]")
{
  Bag<int> b;
  SECTION("adding and clear")
  {
    for(int i = 0; i < 20; i++)
    {
      b.add(i);
    }
    REQUIRE(b.isEmpty()==0);
    REQUIRE(b.getCurrentSize()==20);
    b.clear();
    REQUIRE(b.isEmpty()==1);
    REQUIRE(b.getCurrentSize()==0);
  }

  SECTION("adding again")
  {
    SECTION("0<=bagSize<=maxSize")
    {
      for(int i = 0; i < 10; i++)
      {
        SECTION("b.add( i = " + std::to_string(i) + " )")
        {
          REQUIRE(b.add(i)==1);
        }
      }
    }
    
    SECTION("maxSize <bagSize <= 3*maxSize")
    {
      for(int i = 10; i < 31; i++)
      {
        SECTION("b.add(i = " + std::to_string(i) + ")")
        {
          REQUIRE(b.add(i)==1);
        }
      }
    }
  }
}

TEST_CASE("Checking Frequencies", "[Bag]")
{
  Bag<int> b;
  int tests[] = {0, 1, 1, 2, 3, 4, 5, 6, 7, 7, 7, 12, 12};
  int test_freq[] = {1, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 2, 2};
  int tests_length = 13;

  for(int i = 0; i < tests_length; i++)
  {
    b.add(tests[i]);
  }

  for(int i = 0; i < tests_length; i++)
  {
    REQUIRE(b.getFrequencyOf(tests[i])==test_freq[i]);
  }
}

TEST_CASE("CONTAINS","[Bag]")
{
  Bag<int> b;
  b.add(0);
  b.add(1);

  REQUIRE(b.contains(0)==1);
  REQUIRE(b.contains(1)==1);
  REQUIRE(b.contains(2)==0);

  b.add(2);
  REQUIRE(b.contains(2)==1);
}

TEST_CASE("REMOVE and checkcurrentsize", "[Bag]")
{
  Bag<int> b;
  b.add(0);
  b.add(1);
  b.add(2);
  b.add(3);
  b.add(3);

  REQUIRE(b.getCurrentSize()==5);
  REQUIRE(b.getFrequencyOf(3)==2);
  REQUIRE(b.remove(3)==1);
  REQUIRE(b.getFrequencyOf(3)==1);
  REQUIRE(b.getCurrentSize()==4);

  REQUIRE(b.remove(0)==1);
  REQUIRE(b.getFrequencyOf(0)==0);
  REQUIRE(b.getFrequencyOf(1)==1);
  REQUIRE(b.getFrequencyOf(2)==1);
  REQUIRE(b.getFrequencyOf(3)==1);
  REQUIRE(b.getCurrentSize()==3);
}