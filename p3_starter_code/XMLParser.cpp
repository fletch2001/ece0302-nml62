// Project 3 -- XML Parsing Project

/** XML parsing class implementation.
    @file XMLParser.cpp */

#include <string>
#include <assert.h>
#include "XMLParser.hpp"

// TODO: Implement the constructor here
XMLParser::XMLParser() {
    parseStack =
        new Stack<std::string>;  // new stack for holding elements while parsing
    elementNameBag = new Bag<std::string>;  // new bag for holding elements
    parseSuccess = 0;
}  // end default constructor

// TODO: Implement the destructor here
XMLParser::~XMLParser() {
    clear();  // clear

    delete parseStack;  // delete parseStack
    parseStack = nullptr;

    delete elementNameBag;
    elementNameBag = nullptr;

}  // end destructor

// TODO: Implement the tokenizeInputString method
bool XMLParser::tokenizeInputString(const std::string &inputString) {
    parseSuccess = 0;  // force parseSuccess to 0
    unsigned nextStart;


    // cout << inputString << endl;
    if (inputString.length() == 0) {
        return false;
    }  // base case
    if (inputString[0] != '<' || inputString[inputString.length() - 1] != '>') {
        this->clear();
        return false;
    }  // returns false if first and last char of string are not < and > (also
       // include clear)

    else {
        if (inputString.find('>', 1) == -1) {
            this->clear();
            return false;
        }  // return false and clear if can't find a next >

        unsigned nextEnd = inputString.find('>', 1);  // find next > in string
       // unsigned nextStart;
        unsigned start_index = 0;  // int to offset loop start
        unsigned end_index = 0;    // int to offset loop end

        TokenStruct thisToken;  // temp token struct to fill up

        std::string elementStr;

        if (inputString.find('<', nextEnd) == -1) {
            nextStart = nextEnd + 1;
        }  // only return false if can't find another start tag AND the next tag
           // is not an end tag
        else {
            nextStart = inputString.find('<', nextEnd);
        }

        if (inputString.find('<', 1) < nextEnd + 1) {
            this->clear();
            return false;
        }  // check for another < before the next >
        if (inputString.find('>', nextEnd + 1) < nextStart) {
            this->clear();
            return false;
        }  // check for > before next <

        // cout << inputString[1] << " " << inputString[nextEnd - 1] << endl;

        // checking for declaration
        if (inputString[1] == '?') {  // check that char before next > is a ?
            if (inputString[nextEnd - 1] == '?') {
                thisToken.tokenType =
                    DECLARATION;  // set token type to declaration
                //	cout << inputString << endl;
            } else {  // not a valid declaration; clear class and return false
                this->clear();
                return false;
            }

            for (unsigned i = 2; i < nextEnd - 1; i++) {
                elementStr += inputString[i];  // append character in
                                               // declaration to elementStr
            }

            thisToken.tokenString = elementStr;         // set token string
            tokenizedInputVector.push_back(thisToken);  // push token to vector
            tokenizeInputString(inputString.substr(
                nextStart));  // recursively call tokenize string input with a
                              // substring of input string starting at the next
                              // <
            return true;      // return true when token added to vector
        }
        // check for empty tag
        else if (inputString[nextEnd - 1] == '/') {  // type is empty tag
            thisToken.tokenType = EMPTY_TAG;         // set tag typee
            end_index = 1;                           // set loop end offset to 1
        } else if (inputString[1] == '/') {          // checking for closing tag
            thisToken.tokenType = END_TAG;           // set end tag
            start_index = 1;  // set loop start offset to 1
        } else {
            thisToken.tokenType = START_TAG;  // set start tag otherwise
        }

        // find next end; the next > or space before a >
        unsigned tempEnd = inputString.find(' ', 1);
        if (tempEnd == -1 || tempEnd > nextEnd)
            tempEnd = nextEnd;
        else if (thisToken.tokenType == END_TAG && tempEnd != -1) {
            cout << inputString << "\n" << tempEnd << endl;
            cout << "ill" << endl;
            this->clear();  // clear structure
            return false;  // there is a space before the > in an end tag, which
                           // is illegal
        }

        for (unsigned i = 1 + start_index; i < tempEnd - end_index; i++) {
            if (i - (1 + start_index) == 0 && !isalpha(inputString[i]) ||
                inputString[i] >= 33 && inputString[i] <= 44 ||
                inputString[i] == 46 || inputString[i] == 47 ||
                inputString[i] >= 58 && inputString[i] <= 64 ||
                inputString[i] >= 91 && inputString[i] <= 94 ||
                inputString[i] == 96 ||
                inputString[i] >= 123 && inputString[i] <= 126) {
                this->clear();  // illegal character; clear structure and return
                                // false
                return false;
            }

            elementStr += inputString[i];  // append tag char to element string
        }

        if (thisToken.tokenType != END_TAG)
            elementNameBag->add(elementStr);  // add element name to bag
        thisToken.tokenString = elementStr;   // set token string

        tokenizedInputVector.push_back(thisToken);  // push token to vector

        elementStr.clear();  // clear elementStr

        // read in any content
        elementStr = inputString.substr(nextEnd + 1, nextStart - nextEnd - 1);

        if (elementStr.find_first_not_of(" ") == -1)
            elementStr.clear();  // clear string if string is all whitespace

        // add content to content token
        if (elementStr.length() > 0) {
            tokenizedInputVector.push_back(
                TokenStruct{StringTokenType::CONTENT, std::string(elementStr)});
        }

        // call tokenizeInputString again on substring starting with next <
        return tokenizeInputString(inputString.substr(nextStart));
    }

        // TODO: push all successsful tokens to stack instead and then pop from stack into vector for return

    return true;
    

    //return false;
}  // end

// TODO: Implement a helper function to delete attributes from a START_TAG
// or EMPTY_TAG string (you can change this...)
static std::string deleteAttributes(std::string input) { return input; }

// TODO: Implement the parseTokenizedInput method here
bool XMLParser::parseTokenizedInput() {
    if (!tokenizedInputVector.size()) {
        this->clear();
        return false;
    }

    for (unsigned i = 0; i < tokenizedInputVector.size(); i++) {
        if (tokenizedInputVector[i].tokenType == END_TAG ||
            tokenizedInputVector[i].tokenType == CONTENT ||
            tokenizedInputVector[i].tokenType == EMPTY_TAG) {
            this->clear();
            //	cout << i << ": " << "1" << " " <<
            //tokenizedInputVector[i].tokenType << " " <<
            //tokenizedInputVector[i].tokenString << endl;
            return false;
        } else if (tokenizedInputVector[i].tokenType == START_TAG) {
            break;  // checks that there is a start tag enclosing next tags
        }
    }

    for (unsigned i = 0; i < tokenizedInputVector.size(); i++) {
        if (tokenizedInputVector[i].tokenType == START_TAG) {
            parseStack->push(
                tokenizedInputVector[i].tokenString);  // push start tag name
        } else if (tokenizedInputVector[i].tokenType == END_TAG) {
            if (parseStack->peek() != tokenizedInputVector[i].tokenString) {
                this->clear();  // clear class
                                //	cout << "2" << endl;
                return false;   // if top of stack (last start tag read in) does
                               // not equal the first end tag seen, return false
            } else
                parseStack->pop();  // otherwise, remove start tag from stack
        } else if (tokenizedInputVector[i].tokenType == CONTENT &&
                   parseStack->isEmpty()) {
            this->clear();  // clear class
            return false;   // if there are no start tags in stack, and tag is a
                            // content tag, return false
        }
    }

    if (!parseStack->isEmpty()) {
        this->clear();
        return false;  // case when there is an unmatched start tag
    }

    parseSuccess =
        1;  // if for loop does not return a false, tokenized vector has been
            // successfully parsed. return true and set parse success flag to 1
    return true;
}

// TODO: Implement the clear method here
void XMLParser::clear() {
    parseStack->clear();      // clear parseStack
    elementNameBag->clear();  // clear elementNameBag
    tokenizedInputVector.clear();
}

vector<TokenStruct> XMLParser::returnTokenizedInput() const {
    return tokenizedInputVector;  // return vector
}

// TODO: Implement the containsElementName method
bool XMLParser::containsElementName(const std::string &inputString) const {
    if (!tokenizedInputVector.size() && parseSuccess)
        return false;  // if tokenized vector does not exist or xml string has
                       // not been parsed or is not valid, do not search for
                       // element name

    return elementNameBag->contains(
        inputString);  // use elementBag member function to check whether
                       // inputString is contained in elementNameBag
}

// TODO: Implement the frequencyElementName method
int XMLParser::frequencyElementName(const std::string &inputString) const {
    if (!tokenizedInputVector.size() && parseSuccess)
        return false;  // if tokenized vector does not exist or xml string has
                       // not been parsed or is not valid, do not search for
                       // element name

    return elementNameBag->getFrequencyOf(
        inputString);  // use elementNameBag built in member function to get
                       // frequency
}
