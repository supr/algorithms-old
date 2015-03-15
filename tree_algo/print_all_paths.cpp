#include "bst.h"
using namespace std;

/*
Question:
Given a binary search tree, print all paths of a binary tree from root to leaf.

The algorithm is implemented in:
- void print_current_path(vector<int> &vec);
*/

template <class T>
void Tree<T>::print_current_path(vector<int> &vec) {
  for(int i = 0; i < vec.size(); i++) {
    cout << vec[i] << ' ';
  } 
  cout << '\n';
}

template <class T>  
void Tree<T>::print_all_paths(Tree<T>::Node *root, vector<int> &vec) {
  if(!root) {
    return;
  }
    
  vec.push_back(root->value);
    
  print_all_paths(root->left, vec);
    
  if(!root->left && !root->right) {
    print_current_path(vec);
  }
    
  print_all_paths(root->right, vec);

  vec.pop_back();
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

  vector<int> vec;
  t4.print_all_paths(t4.get_root(), vec);

  return 0;
}
