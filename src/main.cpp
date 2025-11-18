#include "DataBase.hpp"
#include "Expression.hpp"
using namespace std;

int main(int argc, const char *argv[]) {
  DataBase data(argv[1]);
  Expression exp(argv[2]);
  cout << exp.calculate(data);
  return 0;
}
