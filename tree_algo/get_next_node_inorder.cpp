#include "bst.h"
using namespace std;

/*
Problem: Given a binary tree node, return the next node inorder.

The algorithm is implemented in:
- Node *get_next_node_inorder(Node *current) ... uses parent pointers.
- Node *get_next_node_inorder2(Node *current) .. parent pointer is NOT needed in this algorithm.

Time complexity:
both algorithms run in O(h) where h is height of tree.
*/

template <class T>
typename Tree<T>::Node* Tree<T>::get_most_left_node(Tree<T>::Node *current) {
  Tree<T>::Node *prev = current;

  while (current) {
    prev = current;
    current = current->left;
  }

  return prev;
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_next_node_inorder(Tree<T>::Node *current) {
  Tree<T>::Node *next = NULL;

  if (current->right) {
    next = get_most_left_node(current->right);
  }
  else {
    Tree<T>::Node *previous = current;

    while (current) {
      if (current->left == previous) {
        break;
      }
      previous = current;
      current = current->parent;
    }

    if (current) {
      next = current;
    }
  }

  return next;
}
  
template <class T>
typename Tree<T>::Node* Tree<T>::get_next_node_inorder2(Tree<T>::Node *curr) {
  return get_next_node_inorder2_internal(get_root(), curr);
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_next_node_inorder2_internal(Tree<T>::Node *root, Tree<T>::Node *curr) {
  Tree<T>::Node *next = NULL;
    
  if(curr->right) {
    next = get_most_left_node(curr->right);
  }
  else {
    while(root) {
      if(curr->value < root->value) {
        next = root;
        root = root->left;
      }
      else if(curr->value > root->value) {
        root = root->right;
      }
      else {
        break;
      }
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

  t4.print_head(t4, cout);


  Tree<int>::Node *n = t4.get_most_left_node(t4.get_root());
  while (n) {
    cout << n->value << ' ';
    n = t4.get_next_node_inorder(n);
  }

  cout << '\n';
  
  n = t4.get_most_left_node(t4.get_root());
  while (n) {
    cout << n->value << ' ';
    n = t4.get_next_node_inorder2(n);
  }

  return 0;
}
