#include "SegTree.hpp"

SegTree::SegTree() : root(nullptr) {}

SegNode *SegTree::buildTree(const vector<double> arr, Range range) {
  if (range.start == range.end) {
    SegNode *leaf =
        new SegNode(arr[range.start], Range(range.start, range.end));
    return leaf;
  }
  int mid = range.start + (range.end - range.start) / 2;
  SegNode *leftChild = buildTree(arr, Range(range.start, mid));
  SegNode *rightChild = buildTree(arr, Range(mid + 1, range.end));

  // Change this based on the argument
  int currentValue = 0;
  if (operation == "MAX")
    currentValue = max(leftChild->value, rightChild->value);
  else if (operation == "SUM")
    currentValue = leftChild->value + rightChild->value;
  else if (operation == "MIN")
    currentValue = min(leftChild->value, rightChild->value);

  SegNode *parent = new SegNode(currentValue, Range(range.start, range.end));
  parent->left = leftChild;
  parent->right = rightChild;
  return parent;
}

void SegTree::preOrderTraverseHelper(ostream &os, SegNode *current) {
  if (current == nullptr) {
    return;
  }
  cout << current->value << "[" << current->range.start << ", "
       << current->range.end << "] ";
  preOrderTraverseHelper(os, current->left);
  preOrderTraverseHelper(os, current->right);
};

int SegTree::neutral() {
  if (operation == "MIN")
    return 1e9;
  else
    return 0;
}

int SegTree::query(SegNode *current, Range currentRange) {
  if (!current)
    return neutral();

  Range intersection = current->range & currentRange;
  if (intersection.isEmpty())
    return neutral();

  // Si el rango actual está completamente dentro del pedido
  if (current->range.start >= currentRange.start &&
      current->range.end <= currentRange.end)
    return current->value;

  // Parcial → bajar a hijos
  int left = query(current->left, currentRange);
  int right = query(current->right, currentRange);

  if (operation == "MAX")
    return max(left, right);
  else if (operation == "SUM")
    return left + right;
  else if (operation == "MIN")
    return min(left, right);
  else
    return -1;
}

void SegTree::arr2Tree(const vector<double> data, int size) {
  if (size < 1)
    return;
  this->root = buildTree(data, Range(0, size - 1));
};

int SegTree::operator()(Range currentRange) {
  return query(root, currentRange);
};
