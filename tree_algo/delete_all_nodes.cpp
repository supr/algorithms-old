#include "bst.h"
using namespace std;

/*
Question: Delete all the nodes of a Binary Search Treee

The algorithm is implemented in two different ways:
- void delete_all_nodes()
*/

template <class T>
void Tree<T>::delete_all_nodes() {
  delete_all_nodes_internal(root);
  root = NULL;
}

template <class T>  
void Tree<T>::delete_all_nodes_internal(Tree<T>::Node *root) {
  if(!root) {
    return;
  }
    
  delete_all_nodes_internal(root->left);
  delete_all_nodes_internal(root->right);
    
  delete root;
  root = NULL;
}

int main() {
  Tree<int> t;
  t.insert(10);
  t.insert(5);
  t.insert(12);
  t.insert(4);
  t.insert(7);

  t.print_head(t, cout);

  t.delete_all_nodes();
  
  t.print_head(t, cout);
  
  return 0;
}