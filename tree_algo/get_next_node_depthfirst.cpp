#include "bst.h"

/*
Problem: Given a binary tree node, return the next node in depth first order.
The algorithm is implemented in:
- Node *get_next_node_depthfirst(Node *current) ... uses parent pointers.

same algorithm as for get_next_node_preorder

Time complexity:
algorithm runs in O(h) where h is height of tree.
*/

template <class T>  
typename Tree<T>::Node* Tree<T>::get_next_node_depthfirst(Tree<T>::Node *curr) {
  Tree<T>::Node *next = NULL;
  
  if(curr->left) {
    next = curr->left;
  } else if(curr->right) {
    next = curr->right;
  } else {
    Node *prev = curr;
    
    while(curr) {
      if(curr->right && prev == curr->left) {
        next = curr->right;
        break;
      }
      prev = curr;
      curr = curr->parent;
    }
  }
  
  return next;
}

int main() {
  // your code goes here
  
  Tree<int> t;
  t.insert(10);
  t.insert(5);
  t.insert(12);
  t.insert(4);
  t.insert(3);
  t.insert(2);
  t.insert(7);
  t.insert(14);

  t.print_head(t, cout);
  
  Tree<int>::Node *curr = t.get_root();
  
  while(curr) {
    cout << curr->value << ' ';
    curr = t.get_next_node_depthfirst(curr);
  }
  
  return 0;
}