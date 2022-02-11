#include <iostream>
#include <fstream>

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
//using std::iostream;
using std::ifstream;



//KEY: 0 1 1 1 1 1 1 0
const vector<vector<std::string> > palindromeStrings = {{"IsawasI"}, {"Notapalindrome"}, {"Racecar"}, {"AAAA"}, {"IsawasI"}, {"aaAAAAAa"}, {"AAAAA"}, {"bBAaaAa"}, {"BbAaaA"}, {"bBbAAa"}};

// string temp;
// std::getline(tFile, temp);
// std::cout << temp << std::endl;
// tFile.close();

TEST_CASE("test_file"){
	ifstream infile("sentence-palindromes.txt");

	vector<vector<string>> palindromeStrings2;
	
		unsigned trueTests = 0;
		string buf;

		std::getline(infile, buf);

		vector<string> row;

		while(infile) {
			if(buf[0] == '*' && buf[1] == '*'); // comment; skip to next line
			else {
				string tmp;
				for(char c : buf) if(c >= 65 && c <= 90 || c >= 97 && c <= 122)
					tmp += c;
				else if((c == 32 || c == 12) && tmp.length()) 
				{
					row.push_back(tmp); // space or linefeed
					tmp.clear();
				}
				if(tmp.length()) row.push_back(tmp);
				trueTests++;
				
				palindromeStrings2.push_back(row);
				row.clear();
				
			}


			getline(infile, buf);
		}

		//std::cout << trueTests << std::endl;

		infile.close();
		FindPalindrome a;
		unsigned palindromes = 0;

		for(unsigned i = 0; i < 5; i++) {
			// std::cout << i << " ";
			// for(string s : palindromeStrings2[i]) std:: cout << s << " ";
			// std::cout << "    " << a.add(palindromeStrings2[i]);
			// std::cout << std::endl;
			INFO("i = " << i);
			REQUIRE(a.add(palindromeStrings2[i]));
			REQUIRE(a.number());
			palindromes += a.number();
			a.clear();
		}

		CHECK(palindromes >= trueTests);
}

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
		//vector<std::string> l1 = {"Race"};
		vector<std::string> l1 = {"aaa","cbb","ccc"};
		vector<std::string> r1 = {"aaaa","bb","cc"};
		//vector<std::string> r1 = {"car"};
		//fail
		// vector<std::string> l2 = {"aa","bb"};
		// vector<std::string> r2 = {"cca"};

			REQUIRE(a.cutTest2(l1, r1));
			//REQUIRE(a.cutTest2(l2, r2) == 0);
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
	REQUIRE(a.add("AA"));
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
	REQUIRE(a.number() == 6);
	REQUIRE( a.add(vector<string>{"I","was","awI"}));
}