#include "bst.h"
using namespace std;

/*
Question: Convert a BST to a sorted circular doubly-linked list in-place. 
Think of the left and right pointers as synonymous to the previous and next pointers in a doubly-linked list.

The algorithm is implemented in two different ways:
- Node *BST_to_doubly_linked_list()
*/

template <class T>
auto Tree<T>::BST_to_doubly_linked_list() {
  Tree<T>::Node *prev = NULL;
  BST_to_doubly_linked_list_internal(get_root(), &prev);

  return root;
}

template <class T>
void Tree<T>::BST_to_doubly_linked_list_internal(Tree<T>::Node *curr, Tree<T>::Node **prev) {
  if(!curr) {
    return;
  }

  BST_to_doubly_linked_list_internal(curr->left, prev);

  if(!(*prev)) {
    root = curr;
    *prev = curr;
  }
  else {
    curr->left = *prev;
    (*prev)->right = curr;
    *prev = curr;
  }

  BST_to_doubly_linked_list_internal(curr->right, prev);
}

int main() {
  Tree<int> t;
  t.insert(10);
  t.insert(5);
  t.insert(12);
  t.insert(4);
  t.insert(7);

  t.print_head(t, cout);
  
  Tree<int>::Node *prev = NULL;
  Tree<int>::Node *curr = t.BST_to_doubly_linked_list();

  while(curr) {
    cout << curr->value << ' ';
    prev = curr;
    curr = curr->right; 
  }

  cout << '\n' << endl;
  
  while(prev) {
    cout << prev->value << ' ';
    prev = prev->left; 
  }
  
  return 0;
}