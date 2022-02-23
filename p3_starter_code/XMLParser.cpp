// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser()
{
	parseStack = new Stack<std::string>; // new stack for holding elements while parsing
	elementNameBag = new Bag<std::string>; // new bag for holding elements
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
	clear(); // use clear member function
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	if(inputString.length() == 0) {	return false; } // base case
	if(inputString[0] != '<' 
	|| inputString[inputString.length() - 1] != '>') { this->clear(); return false; } // returns false if first and last char of string are not < and > (also include clear)

	else {

		if(inputString.find('>', 1) == -1) { this->clear(); return false; } // return false and clear if can't find a next >

		unsigned nextEnd = inputString.find('>', 1); // find next > in string
		unsigned nextStart;
		unsigned start_index = 0; // int to offset loop start
		unsigned end_index = 0; // int to offset loop end

		TokenStruct thisToken; // temp token struct to fill up

		std::string elementStr;

		if(inputString.find('<', nextEnd) == -1) { nextStart = nextEnd + 1; } // only return false if can't find another start tag AND the next tag is not an end tag
		else { nextStart = inputString.find('<', nextEnd); }

		if(inputString.find('<', 1) < nextEnd) { this->clear(); return false; } // check for another < before the next >
		if(inputString.find('>', nextEnd + 1) < nextStart) { this->clear(); return false; } // check for > before next <

		// checking for declaration
		if(inputString[1] == '?') { // check that char before next > is a ?
			thisToken.tokenType = DECLARATION; // set token type to declaration

			for(unsigned i = 2; i < nextEnd - 1; i++) {
				elementStr += inputString[i]; // append character in declaration to elementStr
			}

			thisToken.tokenString = elementStr; // set token string
			tokenizedInputVector.push_back(thisToken); // push token to vector
			tokenizeInputString(inputString.substr(nextStart)); // recursively call tokenize string input with a substring of input string starting at the next <
			return true; // return true when token added to vector
		}
		// check for empty tag
		else if(inputString[nextEnd - 1] == '/') { // type is empty tag
			thisToken.tokenType = EMPTY_TAG; // set tag typee
			end_index = 1; // set loop end offset to 1
		} else if(inputString[1] == '/') { // checking for closing tag
			thisToken.tokenType = END_TAG; // set end tag
			start_index = 1; // set loop start offset to 1
		} else {
			thisToken.tokenType = START_TAG; // set start tag otherwise
		}
		for(unsigned i = 1 + start_index; i < nextEnd - end_index; i++) {
			if(inputString[i] == ' ') {
				break; // set space index and break
			}
			elementStr += inputString[i]; // append tag character to element string
		}

		parseStack->push(elementStr); // add element name to stack
		thisToken.tokenString = elementStr; // set token string

		tokenizedInputVector.push_back(thisToken); // push token to vector

		elementStr.clear(); // clear elementStr


		// read in any content
		elementStr = inputString.substr(nextEnd + 1, nextStart - nextEnd - 1);

		if(elementStr.find_first_not_of(" ") == -1) elementStr.clear(); // clear string if string is all whitespace

		// add content to content token
		if(elementStr.length() > 0) {
			tokenizedInputVector.push_back(TokenStruct{StringTokenType::CONTENT, std::string(elementStr)});
		}

		// call tokenizeInputString again on substring starting with next <
		tokenizeInputString(inputString.substr(nextStart));



		return true;
	}

	return false;
}  // end

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input)
{
	return input;
}

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput()
{
	return false;
}

// TODO: Implement the clear method here
void XMLParser::clear()
{
	//parseStack->clear(); // clear stack
	delete parseStack; // delete parseStack (also clears it)
	delete elementNameBag;
	tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const
{
	return false;
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const
{
	return -1;
}

