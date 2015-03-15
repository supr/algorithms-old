#include "bst.h"

/*
Problem: Given a binary tree node, return the next node preorder.

- Node *get_next_node_preorder(Node *current) ... uses parent pointers.
- Node *get_next_node_preorder2(Node *current) .. parent pointer is NOT needed in this algorithm.

Time complexity:
both algorithms run in O(h) where h is height of tree.
*/

template <class T>
typename Tree<T>::Node* Tree<T>::get_next_node_preorder(Tree<T>::Node *current) {
  Node *next = NULL;

  if (current->left) {
    next = current->left;
  }
  else if (current->right) {
    next = current->right;
  }
  else {
    Node *previous = current;

    while (current) {
      if (current->left == previous && current->right) {
        break;
      }
      previous = current;
      current = current->parent;
    }

    if (current && current->right) {
      next = current->right;
    }
  }

  return next;
}

template <class T>  
typename Tree<T>::Node* Tree<T>::get_next_node_preorder2(Tree<T>::Node *curr) {
  return get_next_node_preorder2_internal(get_root(), curr);
}

template <class T>  
typename Tree<T>::Node* Tree<T>::get_next_node_preorder2_internal(Tree<T>::Node *root, Tree<T>::Node *curr) {
  Node *next = NULL;
    
  if(curr->left) {
    next = curr->left;
  }
  else if(curr->right) {
    next = curr->right;
  }
  else {
    Node *prev = NULL;
      
    while(root) {
      if(curr->value < root->value) {
        if(root->right) {
          prev = root;
        }
        root = root->left;
      }
      else if(curr->value > root->value) {
        root = root->right;
      }
      else {
        break;
      }
    }
      
    if(prev) {
      next = prev->right;
    }
  }
    
  return next;
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
  t4.insert(6);
  t4.insert(8);
  
  t4.print_head(t4, cout);


  Tree<int>::Node *n = t4.get_root();
  while (n) {
    cout << n->value << ' ';
    n = t4.get_next_node_preorder(n);
  }

  cout << '\n';
  
  n = t4.get_root();
  while (n) {
    cout << n->value << ' ';
    n = t4.get_next_node_preorder2(n);
  }

  return 0;
}
