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
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser()
{
}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	if(inputString[0] != '<' 
	&& inputString[inputString.length() - 1] != '>') { return false; } // returns false if first and last char of string are not < and > (also include clear)

	unsigned nextEnd = inputString.find('>', 1); // find next > in string

	unsigned start_index = 0; // int to offset loop start
	unsigned end_index = 0; // int to offset loop end

	TokenStruct thisToken; // temp token struct to fill up

	std::string elementStr;

	// checking for declaration
	if(inputString[1] == '?') { // check that char before next > is a ?
		if(nextEnd == string::npos) { return false; } // no closing tag found. return false (also include desctruction methods)
		else if(inputString[nextEnd - 1] != '?') { return false; } // if the charcater before the next > is not a ?, then there is an illegal character in the tag and return false and clear
		// ** push back declaration if need be **
		thisToken.tokenType = DECLARATION; // set token type to declaration


		for(unsigned i = 2; i < nextEnd - 1; i++) {
			elementStr += inputString[i]; // append character in declaration to elementStr
		}

		thisToken.tokenString = elementStr;

		tokenizedInputVector.push_back(thisToken); // push token to vector
		return true; // return true when token added to vector
	}
	// check for empty tag
	else if(inputString[nextEnd - 1] == '/') { // type is empty tag
		thisToken.tokenType = EMPTY_TAG; // set tag type
		
		// check that tag name is valid
		end_index = 1;

		// for(unsigned i = 1; i < nextEnd; i++) {
		// 	if(inputString[i] == ' ') {
		// 		break; // set space index and break
		// 	}
		// 	elementStr += inputString[i];
		// }

		// parseStack->push(elementStr); // add element name to stack
		// thisToken.tokenString = elementStr; // set string

		// tokenizedInputVector.push_back(thisToken);
		// return true;

		// // find first whitespace in string
		// unsigned sp = inputString.substr(0, nextEnd).find(' ', 0);

		// for(unsigned i = sp; i < nextEnd - 1; i++) {
		// 	elementStr += inputString[i]; // append characters of attribute to elementStr
		// }

	} else if(inputString[1] == '/') { // checking for closing tag
		start_index = 1;
	// else { // otherwise, tag is a start-tag
	// 	thisToken.tokenType = START_TAG; // set token type
	// 	unsigned sp = 0; // space index
	// 	for(unsigned i = 1; i < nextEnd; i++) {
	// 		if(inputString[i] == ' ') {
	// 			break; // set space index and break
	// 		}
	// 		elementStr += inputString[i];
	// 	}

	// 	parseStack->push(elementStr); // add element name to stack
	// 	thisToken.tokenString = elementStr; // set string
	}

	for(unsigned i = 1 + start_index; i < nextEnd - end_index; i++) {
			if(inputString[i] == ' ') {
				break; // set space index and break
			}
			elementStr += inputString[i];
		}

		parseStack->push(elementStr); // add element name to stack
		thisToken.tokenString = elementStr; // set string

		tokenizedInputVector.push_back(thisToken);


	// loop through string until next >
	// for(unsigned i = 1 + start_index; i < nextEnd; i++) {
	// 	if(inputString[i] >= 32 && inputString[i] <= 47 || inputString[i] >= 58 && inputString[i] <= 64) {
	// 		return false; // invalid character in string
	// 	} else {
	// 		elementStr += inputString[i]; // else append string contents to elementStr
	// 	}
	// }

	std::cout << elementStr << std::endl;

	unsigned nextStart = inputString.find('<', nextEnd);

	// call tokenizeInputString again on substring starting with next <
	tokenizeInputString(inputString.substr(nextStart));

	/* <123456> : l = 8
		str[7] = >
		str[1] = 1
		str[l - 1] = >
		str[l - 2] = 6
	*/


	return true;
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

