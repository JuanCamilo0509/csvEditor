#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class dataColumn {
public:
  vector<double> data;
};

class Headers {
public:
  int count;
  vector<string> headers;
};

class csvReader {
  string path;
  Headers headers;
  vector<dataColumn> columns;
  void setHeaders();

public:
  csvReader(string path) : path(path) {
    setHeaders();
    columns.resize(headers.count);
  };
  void readCsv();
  Headers getHeaders();
  vector<double> getColumn(string columnName);
};
