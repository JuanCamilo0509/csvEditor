// Code adaptation by Juan Camilo from KnightChaser.
// Original code:
// https://gist.github.com/KnightChaser/24af1305e9c0909280beec58e1051845
#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>

#include <algorithm>
#include <vector>
using namespace std;

// redefine operator << to print the vector like just strings

template <typename S>
ostream &operator<<(ostream &os, const vector<S> &vector) {
  // Printing all the elements
  // using <<
  for (auto element : vector) {
    os << element << " ";
  }
  return os;
}

class Expression {
public:
  string expression;
  vector<string> disassembledExpression;
  vector<string> RPNExpression;
  Expression(string expression) : expression(expression) {};
  double calculate();
  double evaluateRPNExpression();
  void disassembleExpression();
  void transformExpressionRPN();
  int operatorPriority(char ch);
};

#endif
