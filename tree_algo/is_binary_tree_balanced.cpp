#include "bst.h"

/*
Question: How would you check if a binary tree is balanced?

The algorithm is implemented in two different ways:
- bool is_tree_balanced1(Node *root)
- bool is_tree_balanced2(Node *root)
*/

template <class T>
bool Tree<T>::is_tree_balanced1(Tree<T>::Node *root) {
  int curr_depth = 0;
  int min_depth = numeric_limits<int>::max();
  int max_depth = numeric_limits<int>::min();
    
  return dfs(root, curr_depth, min_depth, max_depth);
}

template <class T>
bool Tree<T>::dfs(Tree<T>::Node *root, int &curr_depth, int &min_depth, int &max_depth) {
  if (!root) {
    return true;
  }
    
  curr_depth++;
    
  bool val = dfs(root->left, curr_depth, min_depth, max_depth);
  if (!val) {
    return val;
  }
    
  if (!root->left && !root->right) {
    if (curr_depth < min_depth) {
      min_depth = curr_depth;
    }
    if (curr_depth > max_depth) {
      max_depth = curr_depth;
    }
      
    if ((max_depth - min_depth) > 1) {
      return false;
    }
  }
    
  val = dfs(root->right, curr_depth, min_depth, max_depth);
  if (!val) {
    return val;
  }
    
  curr_depth--;
    
  return true;
}

template <class T>
int Tree<T>::get_max_depth(Tree<T>::Node *root) {
  if (!root) {
    return 0;
  }

  return 1 + std::max(get_max_depth(root->left), get_max_depth(root->right));
}

template <class T>
int Tree<T>::get_min_depth(Tree<T>::Node *root) {
  if (!root) {
    return 0;
  }

  return 1 + std::min(get_min_depth(root->left), get_min_depth(root->right));
}

template <class T>
bool Tree<T>::is_tree_balanced2(Tree<T>::Node *root) {
  return abs(get_max_depth(root) - get_min_depth(root)) <= 1;
}

int main() {
  Tree<int> t4;
  t4.insert(10);
  t4.insert(5);
  t4.insert(12);
  t4.insert(4);
  t4.insert(7);

  t4.print_head(t4, cout);

  bool is_tree_well_balanced1 = t4.is_tree_balanced1(t4.get_root());
  bool is_tree_well_balanced2 = t4.is_tree_balanced2(t4.get_root());

  if (is_tree_well_balanced1 && is_tree_well_balanced2) {
    cout << "The Binary tree is well balanced" << endl;
  }
  else {
    cout << "The Binary tree is not well balanced" << endl;
  }
  
  return 0;
}
