#define CATCH_CONFIG_MAIN
#include <iostream>
#include "catch.hpp"
#include "XMLParser.hpp"

using namespace std;

// TODO Implement tests of your Stack class and XMLParser class here

TEST_CASE( "Test Bag add", "[XMLParser]" )
{
	   INFO("Hint: testing Bag add()");
		// Create a Bag to hold ints
		Bag<int> intBag;
		int testSize = 2;
		int bagSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intBag.add(i);
			REQUIRE(success);
			bagSize = intBag.size();
			success = (bagSize == (i+1));
			REQUIRE(success);
		}
}

TEST_CASE( "Test Stack push", "[XMLParser]" )
{
	   INFO("Hint: testing Stack push()");
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 3;
		int stackSize;
		bool success;
		for (int i=0; i<testSize; i++) {
			success = intStack.push(i);
			REQUIRE(success);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
}

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

TEST_CASE( "Test XMLParser tokenizeInputString", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
}

TEST_CASE( "Test Stack handout-0", "[XMLParser]" )
{
		// Create a Stack to hold ints
		Stack<int> intStack;
		int testSize = 10;
		int stackSize;
		bool success = false;
		for (int i=0; i<testSize; i++) {
			intStack.push(i);
			stackSize = intStack.size();
			success = (stackSize == (i+1));
			REQUIRE(success);
		}
		for (int i = testSize-1; i>=0; i--) {
			REQUIRE(intStack.isEmpty() == false);
            int elem = intStack.peek();
			REQUIRE(elem == i);
            REQUIRE(intStack.isEmpty() == false);
			intStack.pop();
		}
        REQUIRE(intStack.isEmpty() == true);
}

TEST_CASE( "Test Stack handout-1", "[XMLParser]" )
{
	   Stack<char> charStack;
       std::string s("Hello world");
       int i = 1;
       for (auto c:s) {
           charStack.push(c);
           REQUIRE(charStack.size() == i);
           i++;
       }
       for (i = 0; i < 5; i++) {
           REQUIRE(charStack.isEmpty() == false);
           char c = charStack.peek();
           REQUIRE(c == s[s.length()-1-i]);
           REQUIRE(charStack.isEmpty() == false);
           charStack.pop();
       }
       REQUIRE(charStack.size() == 6);
       charStack.clear();
       REQUIRE(charStack.isEmpty() == true);      
}

// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test>stuff</test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}


// You can assume that the beginning and the end of CONTENT will not be filled with whitespace
TEST_CASE( "Test XMLParser tokenizeInputString Handout-1", "[XMLParser]" )
{
	   INFO("Hint: tokenize multiple elements test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Note src='gmail'>  <From>Tom</From> <To>Alice</To> </Note>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = { TokenStruct{StringTokenType::DECLARATION, std::string("xml version=\"1.0\" encoding=\"UTF-8\"")},
									TokenStruct{StringTokenType::START_TAG, std::string("Note")},
									TokenStruct{StringTokenType::START_TAG, std::string("From")},
									TokenStruct{StringTokenType::CONTENT, std::string("Tom")},
									TokenStruct{StringTokenType::END_TAG, std::string("From")},
									TokenStruct{StringTokenType::START_TAG, std::string("To")},
									TokenStruct{StringTokenType::CONTENT, std::string("Alice")},
									TokenStruct{StringTokenType::END_TAG, std::string("To")},
									TokenStruct{StringTokenType::END_TAG, std::string("Note")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser parseTokenizedInput Handout-0", "[XMLParser]" )
{
	   INFO("Hint: tokenize single element test of XMLParse");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		string testString = "<test myattr='abcdef'>stuff<this_is_empty_tag/></test>";
		bool success;
		success = myXMLParser.tokenizeInputString(testString);
		REQUIRE(success);
		std::vector<TokenStruct> result = {TokenStruct{StringTokenType::START_TAG, std::string("test")},
											TokenStruct{StringTokenType::CONTENT, std::string("stuff")},
											TokenStruct{StringTokenType::EMPTY_TAG, std::string("this_is_empty_tag")},
											TokenStruct{StringTokenType::END_TAG, std::string("test")}};
		std::vector<TokenStruct> output = myXMLParser.returnTokenizedInput();
		// for(TokenStruct T : output) {
		// 	cout << T.tokenString << endl;
		// }
		REQUIRE(result.size() == output.size());
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		output = myXMLParser.returnTokenizedInput();
		REQUIRE(result.size() == output.size());
		for (int i = 0; i < result.size(); i++) {
			REQUIRE(result[i].tokenType == output[i].tokenType);
			REQUIRE(result[i].tokenString.compare(output[i].tokenString) == 0);
		}
}

TEST_CASE( "Test XMLParser Final Handout-0", "[XMLParser]" )
{
	   INFO("Hint: Product");
		// Create an instance of XMLParse
		XMLParser myXMLParser;
		ifstream myfile ("./TestFile.txt");
		std::string inputString((std::istreambuf_iterator<char>(myfile) ), (std::istreambuf_iterator<char>()) );

		bool success;
		success = myXMLParser.tokenizeInputString(inputString);
		REQUIRE(success);
		success = myXMLParser.parseTokenizedInput();
		REQUIRE(success);
		REQUIRE(myXMLParser.containsElementName("catalog"));
		REQUIRE(myXMLParser.frequencyElementName("catalog") == 1);
		REQUIRE(myXMLParser.containsElementName("product"));
		REQUIRE(myXMLParser.frequencyElementName("product") == 1);
		REQUIRE(myXMLParser.containsElementName("catalog_item"));
		REQUIRE(myXMLParser.frequencyElementName("catalog_item") == 2);
		REQUIRE(myXMLParser.containsElementName("item_number"));
		REQUIRE(myXMLParser.frequencyElementName("item_number") == 2);
		REQUIRE(myXMLParser.containsElementName("size"));
		REQUIRE(myXMLParser.frequencyElementName("size") == 6);
		REQUIRE(myXMLParser.containsElementName("color_swatch"));
		REQUIRE(myXMLParser.frequencyElementName("color_swatch") == 15);
}

TEST_CASE("illegal characters") {
	XMLParser x;
	vector<int> ill_chars = {33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 47, 59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 96, 123, 124, 125, 126};
	vector<int> nums = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};

	for(unsigned i = 0; i < ill_chars.size(); i++) {
		string insert_char;
		insert_char = (char)ill_chars[i];
		string inputString = "<t><ab"+insert_char+"/></t>";
		// cout << inputString << endl;
		x.tokenizeInputString(inputString);
		//REQUIRE(success);
		bool success = x.parseTokenizedInput();
		REQUIRE(!success);
	}

	for(unsigned i = 0; i < nums.size(); i++) {
		string insert_char;
		insert_char = (char)nums[i];
		string inputString = "<t><ab"+insert_char+"/></t>";
		//cout << inputString << endl;
		x.tokenizeInputString(inputString);
		//REQUIRE(success);
		bool success = x.parseTokenizedInput();
		REQUIRE(success);
	}

	for(unsigned i = 0; i < ill_chars.size(); i++) {
		string insert_char;
		insert_char = (char)ill_chars[i];
		string inputString = "<t><"+insert_char+"ab/></t>";
		//cout << inputString << endl;
		x.tokenizeInputString(inputString);
		//REQUIRE(success);
		bool success = x.parseTokenizedInput();
		REQUIRE(!success);
	}

	for(unsigned i = 0; i < nums.size(); i++) {
		string insert_char;
		insert_char = (char)nums[i];
		string inputString = "<t><"+insert_char+"ab/></t>";
		//cout << inputString << endl;
		x.tokenizeInputString(inputString);
		//REQUIRE(success);
		bool success = x.parseTokenizedInput();
		REQUIRE(!success);
	}
}

TEST_CASE("testing invalid strings") {
	XMLParser x;
	std::string inputString = "<test><test/>";
	REQUIRE(x.tokenizeInputString(inputString));
	REQUIRE_FALSE(x.parseTokenizedInput());

	x.clear();

	inputString = "</test>";
	REQUIRE(x.tokenizeInputString(inputString));
	REQUIRE_FALSE(x.parseTokenizedInput());

	x.clear();

	inputString = "<? decl ?><test><test1></test1></test>";
	REQUIRE(x.tokenizeInputString(inputString));
	REQUIRE(x.parseTokenizedInput());

	x.clear();

	inputString = "<? decl ?><test><test1></test></test1>";
	REQUIRE(x.tokenizeInputString(inputString));
	REQUIRE_FALSE(x.parseTokenizedInput());
}

TEST_CASE("empty string") {
	XMLParser x;
	string inputString = "";
	bool success;

	success = x.tokenizeInputString(inputString);
	REQUIRE(!success);

	success = x.parseTokenizedInput();
	REQUIRE(!success);
}

TEST_CASE("testing search and getqty for empty strings") {
	XMLParser x;
	string inputString = "";
	bool success;

	success = x.tokenizeInputString(inputString);
	REQUIRE(!success);

	success = x.parseTokenizedInput();
	REQUIRE(!success);

	success = x.containsElementName("");
	REQUIRE(!success);

	success = x.frequencyElementName("");
	REQUIRE(!success);
}

TEST_CASE("testing search and getqty for valid strings") {
	XMLParser x;
	string inputString = "<?declaration?><xml><s1></s1></xml>";
	bool success;

	success = x.tokenizeInputString(inputString);
	REQUIRE(success);

	success = x.parseTokenizedInput();
	REQUIRE(success);

	success = x.containsElementName("s1");
	REQUIRE(success);

	success = x.containsElementName("xml");
	REQUIRE(success);

	int freq = x.frequencyElementName("xml");
	REQUIRE(freq == 1);

	freq = x.frequencyElementName("s1");
	REQUIRE(freq == 1);
}

TEST_CASE("testing search and getqty for invalid strings") {
	XMLParser x;
	vector<string> inputStrings = {"<?declaration?><xml><s1></s1><xml>","<?declaration?><xml><s1></s1><xml/>"};
	
	for(int i = 0; i < inputStrings.size(); i++) {
	
		bool success;

		success = x.tokenizeInputString(inputStrings[i]);
		REQUIRE(success);

		success = x.parseTokenizedInput();
		REQUIRE(!success);

		success = x.containsElementName("s1");
		REQUIRE(!success);

		success = x.containsElementName("xml");
		REQUIRE(!success);

		int freq = x.frequencyElementName("xml");
		REQUIRE(freq == 0);

		freq = x.frequencyElementName("s1");
		REQUIRE(freq == 0);
	}
}

TEST_CASE("invalid tag name") {
	string inputString = "<pro duct></pro duct>";
	XMLParser x;
	REQUIRE(!x.tokenizeInputString(inputString));

}