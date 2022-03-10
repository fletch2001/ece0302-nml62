#include <stack>
using std::stack;

#include <string>
using std::string;

#include <iostream>

#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {
  char endCh = postfix[postfix.size() -1]; // get last char of postfix
  
  postfix.pop_back(); // remove last char of postfix

  if(!isoperator(endCh)) {
    prefix += endCh; // base case: if last char is an alphabetical character, append to prefix
  } else { // otherwise:
    string tmp; // temp string
    prefix += endCh; // append math symbol to prefix
    convert(postfix, tmp); // convert postfix to empty temp string
    convert(postfix, prefix); // continue with postfix to already initialized prefix string
    prefix+= tmp; // add tmp to prefix
  }

}
