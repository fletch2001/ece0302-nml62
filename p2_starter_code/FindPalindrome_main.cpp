#include <iostream>
#include <fstream>
#include "FindPalindrome.hpp"

using namespace std;

int main()
{
	FindPalindrome f;
	string newString("a");
	vector<string> test = {"Never","a","foot","too","far","even"};
	//vector<string> test = {"AA","AAA","AAAA"};
	cout << "\n******* Project 1 Main *********\n\n";
	for (int i=0; i<3; i++) {
		if(f.add(test)) {
			cout << "Added the string :" << newString << endl;
		} else {
			cout << "ERROR: for some reason unable to add the string: << newString " << endl;
		}
		newString += "a";
	}
	cout << "\nNumber of sentence palindromes are:  " << f.number() << endl;
	cout << "\nThe sentence palindromes are:" << endl;
	vector<vector<string>> vectorList = f.toVector();
	for (int i=0; i<vectorList.size(); i++) {
		for (int j=0; j<vectorList[i].size(); j++) {
			cout << vectorList[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "\n******* Project 1 Main *********\n\n";
	return 0;

/*
	ifstream infile;
	//infile.open("sentence-palindromes.txt");
	infile.open("name.txt");
	vector<vector<string> > palindromeStrings2;
	//infile.open("sentence-palindromes.txt");
	//if(infile.good()) {
		unsigned trueTests = 0;
		string buf;
		unsigned i = 0;
		infile >> buf;
		//std::getline(infile, buf);
		while(infile) {
			if(buf[0] == '*' && buf[1] == '*'); // comment; skip to next line
			else {
				unsigned j = 0;

				for(char c : buf) if(c >= 65 && c <= 90 || c >= 97 && c <= 122)
					palindromeStrings2[i][j]+= c;
				else if(c == 32) j++; // space
				trueTests++;
				i++;
			}
			std::getline(infile, buf);
		}

		FindPalindrome a;

		for(unsigned i = 0; i < palindromeStrings2.size(); i++) {
			a.add(palindromeStrings2[i]);
		}

	cout << "\nNumber of sentence palindromes are:  " << a.number() << endl;
	cout << "\nThe sentence palindromes are:" << endl;
	vector<vector<string>> vectorList = a.toVector();
	for (int i=0; i<vectorList.size(); i++) {
		for (int j=0; j<vectorList[i].size(); j++) {
			cout << vectorList[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "\n******* Project 1 Main *********\n\n";
	return 0;
	*/

}