#pragma once
#include "DataBase.hpp"
#include "SegTree.hpp"
#include <Range.hpp>
#include <functional>
#include <unordered_map>

struct Operator {
  int arity;
  function<string(const vector<string> &, DataBase data)> impl;
};
unordered_map<string, Operator> ops = {
    {"+",
     {2,
      [](const vector<string> &args, DataBase data) {
        return to_string(stod(args[0]) + stod(args[1]));
      }}},
    {"-",
     {2,
      [](const vector<string> &args, DataBase data) {
        return to_string(stod(args[0]) - stod(args[1]));
      }}},
    {"*",
     {2,
      [](const vector<string> &args, DataBase data) {
        return to_string(stod(args[0]) * stod(args[1]));
      }}},
    {"/",
     {2,
      [](const vector<string> &args, DataBase data) {
        return to_string(stod(args[0]) / stod(args[1]));
      }}},
    {"MAX",
     {1,
      [](const vector<string> &args, DataBase data) {
        Range range(args[0]);
        string columnName = args[0].substr(0, args[0].find('['));
        data.readCsv();
        vector<double> column = data.getColumn(columnName);
        SegTree tree;
        tree.setOperation("MAX");
        tree.arr2Tree(column, column.size());
        return to_string(tree(range));
      }}},
    {"MIN",
     {1,
      [](const vector<string> &args, DataBase data) {
        Range range(args[0]);
        string columnName = args[0].substr(0, args[0].find('['));
        data.readCsv();
        vector<double> column = data.getColumn(columnName);
        SegTree tree;
        tree.setOperation("MIN");
        tree.arr2Tree(column, column.size());
        return to_string(tree(range));
      }}},
    {"SUM",
     {1,
      [](const vector<string> &args, DataBase data) {
        Range range(args[0]);
        string columnName = args[0].substr(0, args[0].find('['));
        data.readCsv();
        vector<double> column = data.getColumn(columnName);
        SegTree tree;
        tree.setOperation("SUM");
        tree.arr2Tree(column, column.size());
        return to_string(tree(range));
      }}},
};
