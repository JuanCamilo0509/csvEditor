#pragma once
#include "Range.hpp"
#include <vector>
using namespace std;
class SegNode {
public:
  SegNode *right;
  SegNode *left;
  Range range;
  int value;
  SegNode(int value, Range range)
      : value(value), range(range), right(nullptr), left(nullptr) {};
};

class SegTree {
  string operation;
  friend ostream &operator<<(ostream &os, SegTree tree) {
    tree.preOrderTraverseHelper(os, tree.root);
    os << endl;
    return os;
  }

private:
  SegNode *buildTree(vector<double>, Range range);
  void preOrderTraverseHelper(ostream &os, SegNode *current);
  int query(SegNode *current, Range currentRange);

public:
  SegNode *root;
  SegTree();
  void setOperation(string op) { operation = op; };
  void arr2Tree(vector<double>, int size);
  void preOrderTraverse();
  void tree2Arr(SegTree locarRoot);
  int operator()(Range currentRange);
};
