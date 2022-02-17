#include <iostream>
#include <string>
#include <fstream>

#define CATCH_CONFIG_MAIN
//#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

using std::vector;
using std::string;
using std::ifstream;

std::string stringToLower(const string & value) {
	std::string lower;
	for(unsigned i = 0; i < value.size(); i++) {
		lower += tolower(value[i]);
	}

	return lower;
}

/*******************************************************************************************************/
/* number() and add(vector<string>) not tested in their own test cases but tested throughout all tests */
/*******************************************************************************************************/

//KEY: 0 1 1 1 1 1 1 0

const vector<vector<std::string> > palindromeStrings = {{"IsawasI"}, {"Notapalindrome"}, {"Racecar"}, {"AAAA"}, {"IsawasI"}, {"aaAAAAAa"}, {"AAAAA"}, {"bBAaaAa"}, {"BbAaaA"}, {"bBbAAa"}};
vector<vector<string>> palindromeStrings2;

TEST_CASE("testfile"){
	ifstream infile("sentence-palindromes-modified.txt");
	if(infile) {
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

			infile.close();
			FindPalindrome a;
			unsigned palindromes = 0;

			SECTION( "ordered_palindromes" ) {

				for(unsigned i = 0; i < palindromeStrings2.size(); i++) {
					//for(string s : palindromeStrings2[i]) std::cout << s << " ";
					//std::cout << std::endl; // <-- for debugging only
					REQUIRE( a.add(palindromeStrings2[i]) );
					palindromes += a.number();
					REQUIRE( a.number() >= 1 );
					a.clear();
				}

				REQUIRE(palindromes >= palindromeStrings2.size());
			
			}

			SECTION("unordered-palindromes") {
				vector<vector<string>> palindromeStrings3;
				for(unsigned j = 0; j < palindromeStrings2.size(); j++) {
				vector<unsigned int> indices;
				
				// make vector of ordered indices
				for(unsigned i = 0; i < palindromeStrings2[j].size(); i++) {
					indices.push_back(i);
				}

				std::srand( unsigned (std::time(0)) );

				std::random_shuffle( indices.begin(), indices.end() );

				vector<string> row;

				for(unsigned i = 0; i < palindromeStrings2[j].size(); i++) {
					// std::cout << palindromeStrings2[j][indices[i]] << " ";
					row.push_back(palindromeStrings2[j][indices[i]]);
				}

				REQUIRE(a.add(row));
				REQUIRE(a.number());
				palindromes += a.number();

				a.clear();

				row.clear();
				// std::cout << std::endl;

				}

				REQUIRE(palindromes >= palindromeStrings2.size());
			}
	}
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
		vector<std::string> l1 = {"Ra","ce"};
		vector<std::string> r1 = {"car"};
		//vector<std::string> r1 = {"car"};
		//fail
		vector<std::string> l2 = {"aa","bb"};
		vector<std::string> r2 = {"cca"};

			REQUIRE(a.cutTest2(l1, r1));
			REQUIRE(a.cutTest2(l2, r2) == 0);
		}

	//right is longer than left
		SECTION( "right is longer than") {
			//pass
			vector<std::string> l1 = {"Race"};
			vector<std::string> r1 = {"C","AR"};

			//fail
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

	vector<string> stringR3 = {"noah"};
	vector<string> stringL3 = {"I","not"};


	REQUIRE(a.cutTest2(stringL1, stringR1));
	REQUIRE(a.cutTest2(stringL2, stringR2));
	REQUIRE(!a.cutTest2(stringL3, stringR3));

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

	REQUIRE(a.number() == 2);
}

TEST_CASE( "test add overload" ) {
	FindPalindrome a;
	vector<string> s = {"a","AA","AAA"};
	REQUIRE(a.add(s));
	vector<string> f = {"a","BB","CCC"};
	REQUIRE(!a.add(f));

	a.clear();

	vector<string> f1 = {"a","a","AA","AAA"};
	REQUIRE(!a.add(f1));
}

TEST_CASE( "add only with palindromes" ){
	FindPalindrome a;
	vector<string> s = {"a","AA","AaA"};
	REQUIRE(a.add(s));
	REQUIRE(a.number() == 6);
	REQUIRE( a.add(vector<string>{"I","was","awI"}));
}

TEST_CASE( "test_clear" ) {
	FindPalindrome a;

	REQUIRE( a.add("this"));
	REQUIRE( a.number() == 0 );
	
	REQUIRE( a.add("sht") );
	REQUIRE( a.number() == 0);

	a.clear();

	REQUIRE( a.add("siht") );
	REQUIRE( a.number() == 0);

	REQUIRE( a.add("this") );
	REQUIRE( a.number() == 2);
}


TEST_CASE( "test_getVector" ) {
	FindPalindrome a;

	REQUIRE( a.add("Aman") );
	REQUIRE( a.add("Aplan") );
	REQUIRE( a.add("Acanal") );
	REQUIRE( a.add("Panama") );

	REQUIRE( a.number() == 1 );

	vector<vector<string>> palindromeOutput = a.toVector();

	REQUIRE( palindromeOutput[0][0] == "Aman" );
	REQUIRE( palindromeOutput[0][1] == "Aplan" );
	REQUIRE( palindromeOutput[0][2] == "Acanal" );
	REQUIRE( palindromeOutput[0][3] == "Panama" );

	a.clear();

	REQUIRE( a.add("Race") );
	REQUIRE( a.add("Car") );


	REQUIRE( a.number() == 1 );

	palindromeOutput = a.toVector();

	REQUIRE( palindromeOutput[0][0] == "Race" );
	REQUIRE( palindromeOutput[0][1] == "Car" );

}

TEST_CASE( "test_add(string)" ) {
	FindPalindrome a;

	REQUIRE( a.add("Race") );
	REQUIRE( !a.add("Race") );

	SECTION( "testing illegal characters" ) {
		REQUIRE( !a.add("Race!") );
		REQUIRE( !a.add("R ace"));
		REQUIRE( !a.add( "R1ace") );
	}

	REQUIRE( a.add( "Car" ) );
	REQUIRE( a.number() == 1);
}


// for(unsigned j = 0; j < palindromeStrings2.size(); j++) {
// 	vector<unsigned int> indices;
	
// 	// make vector of ordered indices
// 	for(unsigned i = 0; i < palindromeStrings2[j].size(); i++) {
// 		indices.push_back(i);
// 	}

// 	std::srand( unsigned (std::time(0)) );

// 	std::random_shuffle( indices.begin(), indices.end() );

// 	for(unsigned i = 0; i < palindromeStrings2[j].size(); i++) {
// 		std::cout << palindromeStrings2[j][indices[i]] << " ";
// 	}
// 	std::cout << std::endl;

// }