#include "bst.h"
using namespace std;

/*
Question:
Given a binary search tree, print the elements pre-order iterative and recursive.

Preorder:
1. Visit the root.
2. Traverse the left subtree.
3. Traverse the right subtree.

The algorithm is implemented in:
- void preorder_traversal_recursive(Node *root);
- void preorder_traversal_iterative(Node *root);
*/

template <class T>
void Tree<T>::preorder_traversal_recursive(Tree<T>::Node *root) {
  if(!root) {
    return;
  }

  cout << root->value << ' ';
  preorder_traversal_recursive(root->left);
  preorder_traversal_recursive(root->right);
}

template <class T>
void Tree<T>::preorder_traversal_iterative(Tree<T>::Node *root) {
  stack<Tree<T>::Node*> s;
  s.push(root);

  while(!s.empty()) {
    Tree<T>::Node *curr = s.top();
    s.pop();

    cout << curr->value << ' ';

    if(curr->right) {
      s.push(curr->right);
    }
    if(curr->left) {
      s.push(curr->left);
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

  t4.preorder_traversal_recursive(t4.get_root());
  cout << '\n';
  t4.preorder_traversal_iterative(t4.get_root());

  return 0;
}