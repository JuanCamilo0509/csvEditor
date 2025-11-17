#include "CsvReader.hpp"
#include "Expression.hpp"
using namespace std;

int main(int argc, const char *argv[]) {
  Expression exp(argv[1]);
  cout << exp.calculate();
  return 0;
}
