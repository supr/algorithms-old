#include "bst.h"
using namespace std;

/*
Question:
Given a binary search tree, return the max depth of the tree

The algorithm is implemented in:
- int max_depth(Node *root)
*/

template <class T>
int Tree<T>::max_depth(Tree<T>::Node *root) {
  if(!root) {
    return 0;
  }
  
  return std::max(max_depth(root->left) + 1, max_depth(root->right) + 1);
}
  
template <class T>
int Tree<T>::max_depth2(Tree<T>::Node *root) {
  if(!root) {
    return 0;
  }

  int left_height = max_depth(root->left);
  int right_height = max_depth(root->right);
    
  return std::max(left_height, right_height) + 1;
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

  cout << t4.max_depth(t4.get_root()) << endl;

  cout << t4.max_depth2(t4.get_root()) << endl;
  
  return 0;
}
