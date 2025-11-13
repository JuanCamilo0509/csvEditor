#include "Range.hpp"
#include "SegTree.hpp"
using namespace std;

int main() {
  SegTree segtree;
  int arr[4] = {2, 5, 6, 3};
  segtree.arr2Tree(arr, 4);
  segtree.preOrderTraverse();
  int result = segtree(Range(1, 1));
  cout << result;
}
