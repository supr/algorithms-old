#include "bst.h"

/*
Question: Find the k-th maximum node in a binary search tree
Given a Binary Search tree with nodes with unique integers, and given an integer K, find the kth maximum element from the BST.

The algorithm is implemented in:
- Node *find_k_max_node(Node *root, int k);
*/

template <class T>
void Tree<T>::find_k_max_node_internal(Tree<T>::Node *root, int &counter, int &k, Tree<T>::Node **n) {
  if (!root) {
    return;
  }

  find_k_max_node_internal(root->right, counter, k, n);

  counter++;

  if (counter == k) {
    *n = root;
  }

  find_k_max_node_internal(root->left, counter, k, n);
}

template <class T>
typename Tree<T>::Node* Tree<T>::find_k_max_node(Tree<T>::Node *root, int k) {
  int counter = 0;
  Tree<T>::Node *n = NULL;

  find_k_max_node_internal(root, counter, k, &n);

  return n;
}

int main() {
  Tree<int> t4;
  t4.insert(10);
  t4.insert(5);
  t4.insert(12);
  t4.insert(4);
  t4.insert(3);
  t4.insert(2);
  t4.insert(7);
  t4.insert(14);

  t4.print_head(t4, cout);

  Tree<int>::Node *n = t4.find_k_max_node(t4.get_root(), 2);
  if (n) {
    cout << n->value << endl;
  }

  return 0;
}
