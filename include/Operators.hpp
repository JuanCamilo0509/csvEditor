#include "CsvReader.hpp"
#include "SegTree.hpp"
#include <Range.hpp>
#include <functional>
#include <unordered_map>

struct Operator {
  int arity;
  function<string(const vector<string> &)> impl;
};
unordered_map<string, Operator> ops = {
    {"+",
     {2,
      [](const vector<string> &args) {
        return to_string(stod(args[0]) + stod(args[1]));
      }}},
    {"-",
     {2,
      [](const vector<string> &args) {
        return to_string(stod(args[0]) - stod(args[1]));
      }}},
    {"*",
     {2,
      [](const vector<string> &args) {
        return to_string(stod(args[0]) * stod(args[1]));
      }}},
    {"/",
     {2,
      [](const vector<string> &args) {
        return to_string(stod(args[0]) / stod(args[1]));
      }}},

    {"MAX",
     {1,
      [](const vector<string> &args) {
        Range range(args[0]);
        csvReader csvReader("../dataSet/testData.csv");
        csvReader.readCsv();
        string columnName = args[0].substr(0, args[0].find('['));
        vector<double> data = csvReader.getColumn(columnName);
        SegTree tree;
        tree.setOperation("MAX");
        tree.arr2Tree(data, data.size());
        return to_string(tree(range));
      }}},
    // BUG: MIN(X[4, 7])
    {"MIN",
     {1,
      [](const vector<string> &args) {
        Range range(args[0]);
        csvReader csvReader("../dataSet/testData.csv");
        csvReader.readCsv();
        SegTree tree;
        tree.setOperation("MIN");
        vector<double> data = csvReader.getColumn(0);
        tree.arr2Tree(data, data.size());
        return to_string(tree(range));
      }}},
    {"SUM",
     {1,
      [](const vector<string> &args) {
        Range range(args[0]);
        csvReader csvReader("../dataSet/testData.csv");
        csvReader.readCsv();
        SegTree tree;
        tree.setOperation("SUM");
        tree.arr2Tree(csvReader.getColumn(0), csvReader.getColumn(0).size());
        return to_string(tree(range));
      }}},
};
