#include "bst.h"
using namespace std;

/*
Question: Given values of two nodes in a Binary Search Tree, write a c program to find the Lowest Common Ancestor (LCA). You may assume that both the values exist in the tree.

The algorithm is implemented in:
- Node *lowest_common_ancestor(Node *root, Node *n1, Node *n2)
*/

template <class T>
typename Tree<T>::Node* Tree<T>::lowest_common_ancestor(Tree<T>::Node *root, Tree<T>::Node *n1, Tree<T>::Node *n2) {
  if (!root) {
    return NULL;
  }

  if (root == n1 || root == n2) {
    return root;
  }

  Tree<T>::Node *l = lowest_common_ancestor(root->left, n1, n2);
  Tree<T>::Node *r = lowest_common_ancestor(root->right, n1, n2);

  // if we have found one node on right side of the node and other on left side,then 
  // the given node is LCA
  if (l && r) {
    return root;
  }

  // p and q are on the same branch
  return l ? l : r;
    
  /* the macro above means: 
  // if we have found one node on the left side, we don't look below that node, and we return 
  // to parent node to look for right sub tree for the other node
  else if(l != Null)
    return l;
  // if we have found one node on the right side, we don't look below that node, and we return 
  // to parent node to check if other node was found in the left tree then return LCA
  else
    return r;
  */
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

  Tree<int>::Node *ancestor = t4.lowest_common_ancestor(t4.get_root(), t4.get_root()->left->left, t4.get_root()->left->right);

  if (ancestor) {
    cout << ancestor->value << endl;
  }

  return 0;
}
