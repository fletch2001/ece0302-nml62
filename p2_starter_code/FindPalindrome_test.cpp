#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

// TEST_CASE( "Test FindPalindrome add a non-allowable word", "[FindPalindrome]" )
// {
// 	INFO("Hint: add a single non-allowable word");
// 	FindPalindrome b;
// 	REQUIRE(!b.add("kayak1"));
// }

// #include <vector>
using std::vector;
using std::string;

//KEY: 0 1 1 1 1 1 1 0
const vector<vector<std::string> > palindromeStrings = {{"IsawasI"}, {"Notapalindrome"}, {"Racecar"}, {"AAAA"}, {"IsawasI"}, {"aaAAAAAa"}, {"AAAAA"}, {"bBAaaAa"}, {"BbAaaA"}, {"bBbAAa"}};

TEST_CASE( "cutTest1" , "[cut-tests]" ) {
	FindPalindrome a;

	vector<std::string> stringA = {"a","a"};
	vector<std::string> stringB = {"bb","zz"};
	vector<std::string> stringC = {"cc","y","zz"};
	vector<std::string> stringD = {"dd","yyy","fff"};
	
	//vector<std::string> bigString.insert(stringA.)

	//vector<vector<std::string>> testString = {{"a","a"}, {"bb","zz"}, {"cc","y","zz"}, {"dd","yyy","ff"}};

	//vector<vector<string>> testVector;

	REQUIRE(a.cutTest1(palindromeStrings[0]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[1]) == 0);
	REQUIRE(a.cutTest1(palindromeStrings[2]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[3]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[4]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[5]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[6]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[7]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[8]) == 1);
	REQUIRE(a.cutTest1(palindromeStrings[9]) == 0);
	REQUIRE(a.cutTest1(stringA) == 1);
	REQUIRE(a.cutTest1(stringB) == 1);
	REQUIRE(a.cutTest1(stringC) == 1);
	REQUIRE(a.cutTest1(stringD) == 0);

}

TEST_CASE( "cutTest2" ) {
	FindPalindrome a;

	//left is longer than right
		SECTION( "left is longer than right" ) {
		//pass
		vector<std::string> l1 = {"Ra","ce"};
		vector<std::string> r1 = {"car"};
		//fail
		vector<std::string> l2 = {"aa","bb"};
		vector<std::string> r2 = {"cca"};

			REQUIRE(a.cutTest2(l1, r1));
			REQUIRE(a.cutTest2(l2, r2) == 0);
		}

	//right is longer than left
		SECTION( "right is longer than") {
			//pass
			vector<std::string> l1 = {"Rac"};
			vector<std::string> r1 = {"e","car"};

			vector<std::string> l2 = {"aab"};
			vector<std::string> r2 = {"bbb","bcca"};

			REQUIRE(a.cutTest2(l1, r1));
			REQUIRE(a.cutTest2(l2, r2) == 0);
		}	

	//equal lengths

	vector<string> stringL1 = {"I","saw"};
	vector<string> stringR1 = {"as","I"};

	vector<string> stringL2 = {"I","was","and"};
	vector<string> stringR2 = {"ndasawI"};

	vector<string> stringL3 = {"I","not"};


	REQUIRE(a.cutTest2(stringL1, stringR1));
	REQUIRE(a.cutTest2(stringL2, stringR2));

}

TEST_CASE( "test add" ) {
	FindPalindrome a;
	REQUIRE(a.add("a"));
	REQUIRE(!a.add("A"));

	REQUIRE(a.add("testing"));
	REQUIRE(!a.add("teSTInG"));

	REQUIRE(!a.add("testing!"));
	REQUIRE(!a.add("TESTING"));
	REQUIRE(!a.add("two words"));
}

TEST_CASE( "test add overload" ) {
	FindPalindrome a;
	vector<string> s = {"a","AA","AAA"};
	REQUIRE(a.add(s));
	vector<string> f = {"a","BB","CCC"};
	REQUIRE(!a.add(f));
}

TEST_CASE( "add only with palindromes" ){
	FindPalindrome a;
	vector<string> s = {"a","AA","AaA"};
	REQUIRE(a.add(s));
	REQUIRE(a.number() == 1);
}