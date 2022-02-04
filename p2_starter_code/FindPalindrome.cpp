#include <string>
#include <vector>
#include <iostream>
#include <locale> 
#include "FindPalindrome.hpp"

using namespace std;

//------------------- HELPER FUNCTIONS -----------------------------------------


// non-class helper functions go here, should be declared as "static" so that
// their scope is limited
// helper function to convert string to lower case
static void convertToLowerCase(string & value)
{
	locale loc;
	for (int i=0; i<value.size(); i++) {
		value[i] = tolower(value[i],loc);
	}
}

static std::string stringToLower(const string & value) {
	std::string lower;
	for(unsigned i = 0; i < value.size(); i++) {
		lower += tolower(value[i]);
	}

	return lower;
}

static string removeSpaces(const string & value) {
	string noSpaces;
	for(unsigned i = 0; i < value.size(); i++) {
		if(value[i] != ' ') noSpaces.append(1, value[i]);
	}
	return noSpaces;
}

//------------------- PRIVATE CLASS METHODS ------------------------------------


// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(vector<string>
        candidateStringVector, vector<string> currentStringVector)
{

	// TODO need to implement this recursive function!

	// check cut test 1
	if(!cutTest1(candidateStringVector)) return;

	vector<string> left;
	vector<string> right;

	for(unsigned i = 0; i < candidateStringVector.size() / 2; i++) {
		left.push_back(candidateStringVector[i]);
		right.push_back(candidateStringVector[i + candidateStringVector.size() / 2]);
	}

	// check cut test 2
	if(!cutTest2(left, right)) return;

	string testString;

	// add strings to test
	for(string s : candidateStringVector) {
		testString += s;
	}

	//if string is a palindrome, 
	if(isPalindrome(testString)) { 
		num_palindromes++;
		palindromes.push_back(candidateStringVector);
	}

	vector<string> newCandidate;

	newCandidate[0] = candidateStringVector[candidateStringVector.size() - 1];

	for(unsigned i = 1; i < candidateStringVector.size(); i++) {
		newCandidate[i] = candidateStringVector[i - 1];
	}

	recursiveFindPalindromes( , currentStringVector);
}

// private function to determine if a string is a palindrome (given, you
// may change this if you want)
bool FindPalindrome::isPalindrome(string currentString) const
{
	locale loc;
	// make sure that the string is lower case...
	convertToLowerCase(currentString);
	// see if the characters are symmetric...
	int stringLength = currentString.size();
	for (int i=0; i<stringLength/2; i++) {
		if (currentString[i] != currentString[stringLength - i - 1]) {
			return false;
		}
	}
	return true;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// set number of palindromes to 0
	num_palindromes = 0;
}

FindPalindrome::~FindPalindrome()
{
	// clear vectors
	palindromes.clear();
	candidate_strings.clear();
}

int FindPalindrome::number() const
{
	//return number of palindromes
	return num_palindromes;
}

void FindPalindrome::clear()
{
	// reset number of palindromes
	num_palindromes = 0;

	//clear vectors
	palindromes.clear();
	candidate_strings.clear();
}

bool FindPalindrome::cutTest1(const vector<string> & stringVector)
{
	// make list of characters a-z (lowercase)
	// list is index by ascii code

	const unsigned ascii_a = 97;
	unsigned stringLength = 0; // keeps track of number of characters total
	unsigned uniqueChars = 0;

	// vector containing count of each ascii letter (lowercase only) in string
	vector<unsigned int> charCount(26);
	
	// fill vector with zeros
	std::fill(charCount.begin(), charCount.end(), 0);

	for(unsigned i = 0; i < stringVector.size(); i++) {
		for(unsigned j = 0; j < stringVector[i].length(); j++) {
			
			// takes lowercase value of string - ascii_a, which is the lowest possible character value
			// that can occur in the set and adds 

			//incremement number of unique characters for string
			if (charCount[tolower(stringVector[i][j]) - ascii_a] == 0) uniqueChars++;
			charCount[tolower(stringVector[i][j]) - ascii_a]++;
			stringLength++;
		}
	}

	//if there are as many unique characters as the length of the string, the string is not a palindrome
	if (uniqueChars == stringLength) {
		return false;
	}

	// if string is of even length, return false after first occurence of odd number of characters
	if(stringLength % 2 == 0) {
		for(unsigned i = 0; i < charCount.size(); i++) {
			if(!(charCount[i] % 2 == 0)) return false;
		}
		return true;

	} else {

		// one odd char occurence flag
		bool one_odd_char_occurence = false;

		// loop through charCount vector to verify property #1
		for(unsigned i = 0; i < charCount.size(); i++) {
			//if there are an odd number of occurences of a character AND there has not been an odd number occurrence AND the string is not even in length
			if(!(charCount[i] % 2 == 0)) {
				if(!one_odd_char_occurence) {
					// sets flag if not set already
					one_odd_char_occurence = true;
				// if flag was already set, function will return false and does not pass cut test 1
				} else return false;
			}
		}

		// returns true because false condition was already tested
		return true;
	}
}

bool FindPalindrome::cutTest2(const vector<string> & stringVector1,
                              const vector<string> & stringVector2)
{
	//initialize empty strings
	string leftStr = "";
	string rightStr = "";
	
	//determine min size
	if(stringVector1.size() > stringVector2.size()) {

		// copy right vec number of strings from left and right vec
		/** purpose is to make a string of each vector that has no spaces for comparison */
		for(unsigned i = 0; i < stringVector2.size(); i++) {
			leftStr += stringVector1[i];
			rightStr += stringVector2[i];
		}
		
	} else {

		// copy right vec number of strings from left and right vec
		/** purpose is to make a string of each vector that has no spaces for comparison */
		for(unsigned i = 0; i < stringVector1.size(); i++) {
			leftStr += stringVector1[i];
			rightStr += stringVector2[i];
		}
	}

	//if left string is longer than right, iterate through strings up to right size
	if(leftStr.length() > rightStr.length()) {

		//iterate by right string length starting from rightmost character in right and leftmost in left
		for(unsigned j = rightStr.length() - 1; j > 0; j--) {
			if(tolower(leftStr[rightStr.length() - j - 1]) != tolower(rightStr[j])) return false;
		}

	} else {

		//iterate by right string length starting from rightmost character in right and leftmost in left
		for(unsigned j = 0; j < leftStr.length(); j++) {
			if(tolower(leftStr[j]) != tolower(rightStr[rightStr.length() - 1 - j])) return false;
		}

	}
	
	// function returns true because function will return false if strings do not pass cut test 2
	return true;
}

bool FindPalindrome::add(const string & value)
{
	// check that string (in lower case) does not match a string already part of the set
	for(string cs : candidate_strings) {
		if (stringToLower(cs) == stringToLower(value)) return false;
	}

	// checks that each character in the string is between a-z and A-Z
	// checks by making sure that the lowercase ASCII value of each character is with in the lowercase a-z ASCII range
	for(char c : value) {
		if(tolower(c) < 97 || tolower(c) > 122) return false;
	}

	// add string to vector
	candidate_strings.push_back(value);

	// call recursiveFindPalindrome
	return true;
}

bool FindPalindrome::add(const vector<string> & stringVector)
{
	for(string s : stringVector) {

		for(string cs : candidate_strings) {
		if (stringToLower(cs) == stringToLower(s)) return false;
		}

		// checks that each character in the string is between a-z and A-Z
		// checks by making sure that the lowercase ASCII value of each character is with in the lowercase a-z ASCII range
		for(char c : s) {
			if(tolower(c) < 97 || tolower(c) > 122) return false;
		}
	}

	// add each string to candidate vector
	for(string s : stringVector) {
		candidate_strings.push_back(s);
	}

	// call recursiveFindPalindrome

	return true;
}

vector< vector<string> > FindPalindrome::toVector() const
{
	// return vector of vector of palindrome sentences
	return palindromes;
}

