#include "bst.h"

/*
Question:
Given a binary search tree, return the min depth of the tree

The algorithm is implemented in:
- int min_depth(Node *root)
*/

template <class T>
int Tree<T>::min_depth1(Tree<T>::Node *root) {
  if(!root) {
    return 1;
  }
  
  return std::min(min_depth1(root->left) + 1, min_depth1(root->right) + 1);
}

template <class T>  
int Tree<T>::min_depth2(Tree<T>::Node *root) {
  if(!root) {
    return 1;
  }
  
  int left_hight = min_depth2(root->left);
  int right_hight = min_depth2(root->right);
    
  return std::min(left_hight, right_hight) + 1;
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

  cout << t4.min_depth1(t4.get_root()) << endl;

  cout << t4.min_depth2(t4.get_root()) << endl;
  
  return 0;
}
