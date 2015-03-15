#include "bst.h"
using namespace std;

/*
Question: How to verify whether a binary tree is a binary search tree?

Analysis: Binary search tree is an important data structure. It has a specific character: Each node is greater than or equal to 
nodes in its left sub-tree, and less than or equal to nodes in its right sub-tree.

The algorithm is implemented in:
- bool is_BST1();
- bool is_BST2();
*/

template <class T>
bool Tree<T>::is_BST_internal1(Tree<T>::Node *root, int min, int max) {
  if (!root) {
    return true;
  }

  if (root->value < min || root->value > max) {
    return false;
  }

  return is_BST_internal1(root->left, min, root->value) &&
         is_BST_internal1(root->right, root->value, max);
}

template <class T>
bool Tree<T>::is_BST1() {
  int min = numeric_limits<int>::min();
  int max = numeric_limits<int>::max();

  return is_BST_internal1(get_root(), min, max);
}

template <class T>
bool Tree<T>::is_BST_internal2(Tree<T>::Node *root, int &prev_value) {
  if (!root) {
    return true;
  }

  if (!is_BST_internal2(root->left, prev_value)) {
    return false;
  }

  if (root->value < prev_value) {
    return false;
  }

  prev_value = root->value;

  return is_BST_internal2(root->right, prev_value);
}

template <class T>
bool Tree<T>::is_BST2() {
  int prev_value = numeric_limits<int>::min();

  return is_BST_internal2(get_root(), prev_value);
}

int main() {
  Tree<int> t1;
  t1.insert(3);
  t1.insert(1);
  t1.insert(5);
  t1.get_root()->right->value = 2;

  bool is_bin_tree1 = t1.is_BST1();

  if (is_bin_tree1) {
    cout << "The tree is a binary tree" << endl;
  }
  else {
    cout << "The tree is not a binary tree" << endl;
  }

  bool is_bin_tree2 = t1.is_BST2();

  if (is_bin_tree2) {
    cout << "The tree is a binary tree" << endl;
  }
  else {
    cout << "The tree is not a binary tree" << endl;
  }
  
  
  Tree<int> t2;
  t2.insert(3);
  t2.insert(1);
  t2.insert(5);
  t2.insert(2);

  is_bin_tree1 = t2.is_BST1();

  if (is_bin_tree1) {
    cout << "The tree is a binary tree" << endl;
  }
  else {
    cout << "The tree is not a binary tree" << endl;
  }
  
  is_bin_tree2 = t2.is_BST2();

  if (is_bin_tree2) {
    cout << "The tree is a binary tree" << endl;
  }
  else {
    cout << "The tree is not a binary tree" << endl;
  }
  
  return 0;
}