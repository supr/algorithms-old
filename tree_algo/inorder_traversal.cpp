#include "bst.h"
using namespace std;

/*
Question:
Given a binary search tree, print the elements in-order iterative and recursive.

Inorder:
1. Traverse the left subtree.
2. Visit the root.
3. Traverse the right subtree.

The algorithm is implemented in:
- void inorder_traversal_recursive(Node *root);
- void inorder_traversal_iterative(Node *root);
*/

template <class T>
void Tree<T>::inorder_traversal_recursive(Tree<T>::Node *root) {
  if(!root) {
    return;
  }

  inorder_traversal_recursive(root->left);

  cout << root->value << ' ';

  inorder_traversal_recursive(root->right);
}

template <class T>
void Tree<T>::inorder_traversal_iterative(Tree<T>::Node *root) {
  stack<Tree<T>::Node*> s;
  Tree<T>::Node *curr = root;
    
  while(!s.empty() || curr) {
    if(curr) {
      s.push(curr);
      curr = curr->left;
    }
    else {
      curr = s.top();
      s.pop();
        
      cout << curr->value << ' ';
        
      curr = curr->right;
    }
  }
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

  t4.inorder_traversal_recursive(t4.get_root());
  cout << '\n';
  t4.inorder_traversal_iterative(t4.get_root());

  return 0;
}
