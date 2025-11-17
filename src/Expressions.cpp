// Code adaptation by Juan Camilo from KnightChaser.
// Original code:
// https://gist.github.com/KnightChaser/24af1305e9c0909280beec58e1051845

#include "Expression.hpp"
#include "Operators.hpp"

int Expression::operatorPriority(char ch) {
  if (ch == '+' || ch == '-')
    return 1;
  if (ch == '*' || ch == '/')
    return 2;
  return 0;
}

void Expression::disassembleExpression() {
  // BUG: Decimal points not allow.
  // BUG: Negative number not allow.
  // Disassemble each number and operator from the given expression.
  string numberRangeStringBuffer;
  string alphaStringBuffer;

  for (char ch : expression) {
    if (isdigit(ch) || ch == ',')
      if (!alphaStringBuffer.empty() && alphaStringBuffer[1] == '[')
        alphaStringBuffer.push_back(ch);
      else
        numberRangeStringBuffer.push_back(ch);
    else if (isalpha(ch))
      alphaStringBuffer.push_back(ch);
    else if (ch == '[') {
      alphaStringBuffer.push_back(ch);
    } else if (ch == ']') {
      alphaStringBuffer.push_back(ch);
      disassembledExpression.push_back(alphaStringBuffer);
      alphaStringBuffer.clear();

    } else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '(' ||
               ch == ')') {
      if (!numberRangeStringBuffer.empty()) {
        disassembledExpression.push_back(numberRangeStringBuffer);
        numberRangeStringBuffer.clear();
      }
      if (!alphaStringBuffer.empty()) {
        disassembledExpression.push_back(alphaStringBuffer);
        alphaStringBuffer.clear();
      }
      disassembledExpression.push_back(string(1, ch));
    }
  }
  if (!numberRangeStringBuffer.empty()) {
    disassembledExpression.push_back(numberRangeStringBuffer);
  }
  if (!alphaStringBuffer.empty()) {
    disassembledExpression.push_back(alphaStringBuffer);
  }
}

void Expression::transformExpressionRPN() {
  // Convert disassembled vector to the reversed polish notation style
  stack<string> operators; // for operators

  disassembleExpression();
  for (string unit : disassembledExpression) {
    // 1. operands goes straightly
    if (isdigit(unit[0]) || unit[1] == '[') {
      RPNExpression.push_back(unit);
      continue;
    }

    else if (isalpha(unit[0])) {
      operators.push(unit);
      continue;
    }

    // 2. Push if the stack is void or unit is "("
    else if (operators.empty() || unit == "(") {
      operators.push(unit);
      continue;
    }

    // 3. If unit is ")", then export the output until "("
    else if (unit == ")") {
      while (operators.top() != "(") {
        RPNExpression.push_back(operators.top());
        operators.pop();
      }
      operators.pop(); // delete "(" itself
      if (!operators.empty() && isalpha(operators.top()[0])) {
        RPNExpression.push_back(operators.top());
        operators.pop();
      }
      continue;
    }

    // 4. If unit is having a higher priority than the top (two operators
    // conflict), just push
    else if (operatorPriority(operators.top()[0]) < operatorPriority(unit[0])) {
      operators.push(unit);
      continue;
    }

    // 5. If unit is having the same or a lower priority than the top (two
    // operators conflict), pop and repeat the process
    else {
      while (!operators.empty() && (operatorPriority(operators.top()[0]) >=
                                    operatorPriority(unit[0]))) {
        RPNExpression.push_back(operators.top());
        operators.pop();
      }
      operators.push(unit); // then push the current unit
    }
  }

  // If the operators stack is still having some elements, export everything
  while (!operators.empty()) {
    RPNExpression.push_back(operators.top());
    operators.pop();
  }
}

double Expression::evaluateRPNExpression() {
  stack<string> numbers;

  for (string unit : RPNExpression) {
    if (isdigit(unit[0]) || unit[1] == '[') {
      // If unit is a number, put to the number stack
      numbers.push(unit);
    } else if (ops.find(unit) != ops.end()) {
      const Operator &op = ops[unit];
      vector<string> arguments;
      for (int i = 0; i < op.arity; i++) {
        arguments.push_back(numbers.top());
        numbers.pop();
      }
      reverse(arguments.begin(), arguments.end());
      string result = op.impl(arguments);
      numbers.push(result);
    }
  }

  return stod(numbers.top());
}

double Expression::calculate() {
  transformExpressionRPN();
  return evaluateRPNExpression();
}
