#include "bst.h"
using namespace std;

/*
Question: 
All nodes along children pointers from root to leaf nodes form a path in a binary tree. Given a binary tree and a number, please print 
out all of paths where the sum of all nodes value is same as the given number.

For instance, if inputs are the binary tree below and a number 22, two paths with be printed: One is the path contains 
node 10 and 12, and the other contains 10, 5 and 7.

       10
     5    12
   4   7

The algorithm is implemented in two different ways:
- get_paths_with_sum_iterative
- get_paths_with_sum_recursive
*/

template <class T>
void Tree<T>::print_all_paths_with_sum_iterative(Tree<T>::Node *root, const int sum) {
  vector<int> current_path;
  int current_total_sum = 0;
  stack<Tree<T>::Node*> s;
  s.push(root);

  while (!s.empty()) {
    Tree<T>::Node *curr = s.top();
    s.pop();

    current_path.push_back(curr->value);
    current_total_sum += curr->value;
    
    // if the sum of the current value equals the sum we are looking for
    // we store the current path
    if (current_total_sum == sum && 
        !curr->left && 
        !curr->right) {
      print_current_path(current_path);
    }

    bool has_child = false;
    if (curr->right) {
      s.push(curr->right);
      has_child = true;
    }
    if (curr->left) {
      s.push(curr->left);
      has_child = true;
    }

    if (!has_child) {
      Tree<T>::Node *c = curr;
      Tree<T>::Node *prev = NULL;

      while (c && !current_path.empty()) {
        if (prev == c->left && c->right) {
          break;
        }

        current_total_sum -= current_path.back();

        prev = c;
        current_path.pop_back();
        c = c->parent;
      }
    }
  }
}

template <class T>
void Tree<T>::print_current_path(vector<int> &vec) {
  for(int i = 0; i < vec.size(); i++) {
    cout << vec[i] << ' ';
  } 
  cout << '\n';
}

template <class T>  
void Tree<T>::print_all_paths_with_sum_recursive(Tree<T>::Node *root, const int sum) {
  int curr_sum = 0;
  vector<int> curr_path;
    
  return print_all_paths_with_sum_util(root, curr_path, curr_sum, sum);
}

template <class T>  
void Tree<T>::print_all_paths_with_sum_util(Tree<T>::Node *root, vector<int> &curr_path, int &curr_sum, const int sum) {
  if(!root) {
    return;
  }
    
  curr_path.push_back(root->value);
  curr_sum += root->value;
    
  if (!root->left && 
      !root->right && 
      curr_sum == sum) {
    print_current_path(curr_path);
  }
    
  print_all_paths_with_sum_util(root->left, curr_path, curr_sum, sum);
  print_all_paths_with_sum_util(root->right, curr_path, curr_sum, sum);

  curr_path.pop_back();
  curr_sum -= root->value;
}

int main() {
  Tree<int> t4;
  t4.insert(10);
  t4.insert(5);
  t4.insert(12);
  t4.insert(4);
  t4.insert(7);

  t4.print_head(t4, cout);

  t4.print_all_paths_with_sum_iterative(t4.get_root(), 22);
  t4.print_all_paths_with_sum_recursive(t4.get_root(), 22);

  return 0;
}