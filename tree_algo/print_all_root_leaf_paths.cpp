#include "bst.h"

/*
Question:
Given a binary tree, print all root-to-leaf paths 
*/

template <class T>
void Tree<T>::print_paths_from_root(Tree<T>::Node *root) {
  vector<Tree<T>::Node*> s;
    
  print_paths_from_root_util(root, s);
}

template <class T>  
void Tree<T>::print_paths_from_root_util(Tree<T>::Node *root, vector<Tree<T>::Node*> &s) {
  if (!root) {
    return;
  }
    
  s.push_back(root);
    
  if(!root->left && !root->right) {
    for (auto it = s.begin(); it != s.end(); it++) {
      cout << (*it)->value << ' ';
    } 
    cout << '\n';
  }
    
  print_paths_from_root_util(root->left, s);
  print_paths_from_root_util(root->right, s);
 
  s.pop_back();
}

int main() {
  Tree<int> t4;
  t4.insert(10);
  t4.insert(8);
  t4.insert(3);
  t4.insert(9);
  t4.insert(14);
  t4.insert(15);

  t4.get_root()->left->right->value = 5;
  t4.get_root()->right->value = 2;
  t4.get_root()->right->right->value = 2;
  
  t4.print_head(t4, cout);

  t4.print_paths_from_root(t4.get_root());

  return 0;
}