#pragma once
#include <iostream>
using namespace std;
class Range {
public:
  int start;
  int end;
  Range(int start, int end) : start(start), end(end) {
    if (start > end)
      throw runtime_error("Lower bound is greater than upper bound");
  };

  Range(string expression) {
    size_t open = expression.find('[');
    size_t comma = expression.find(',');
    size_t close = expression.find(']');

    // Extraer substrings de forma directa
    start = stoi(expression.substr(open + 1, comma - (open + 1)));
    end = stoi(expression.substr(comma + 1, close - (comma + 1)));
  }

  bool isEmpty() { return start == -1 && end == -1; };

  bool operator==(const Range &other) const {
    return start == other.start && end == other.end;
  }

  Range operator&(const Range &other) const {
    int lowerBound = max(start, other.start);
    int upperBound = min(end, other.end);
    if (lowerBound <= upperBound)
      return Range(lowerBound, upperBound);
    return Range(-1, -1); // Empty intersection
  }
};
