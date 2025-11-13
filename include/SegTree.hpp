#pragma once
#include "Range.hpp"
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
public:
  SegNode *root;

private:
  SegNode *buildTree(const int arr[], Range range);
  void preOrderTraverseHelper(SegNode *current);
  int query(SegNode *current, Range currentRange);

public:
  SegTree();
  void arr2Tree(const int arr[], int size);
  void preOrderTraverse();
  void tree2Arr(SegTree locarRoot);
  int operator()(Range currentRange);
};
