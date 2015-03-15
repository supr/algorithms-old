#include "bst.h"
using namespace std;

/*
 Problem: Trim Binary Search Tree
 Given the root of a binary search tree and 2 numbers min and max, trim the tree such
 that all the numbers in the new tree are between min and max (inclusive). The
 resulting tree should still be a valid binary search tree.
 */

template <class T>
void Tree<T>::trim_BST(Tree<T>::Node *curr, int min, int max) {
  root = trim_BST_internal(curr, min, max);
}
 
template <class T>   
typename Tree<T>::Node* Tree<T>::trim_BST_internal(Tree<T>::Node *root, int min, int max) {
  // Base Case
  if (root == NULL) {
    return NULL;
  }
        
  // First fix the left and right subtrees of root
  root->left = trim_BST_internal(root->left, min, max);
  root->right = trim_BST_internal(root->right, min, max);
        
  // Now fix the root.  There are 2 possible cases for root
  // 1.a) Root's key is smaller than min value (root is not in range)
  if (root->value < min) {
    Tree<T>::Node *rChild = root->right;
    if(rChild) {
      rChild->parent = root->parent;
    }
    delete root;
    return rChild;
  }
  // 1.b) Root's key is greater than max value (root is not in range)
  if (root->value > max) {
    Tree<T>::Node *lChild = root->left;
    if(lChild) {
      lChild->parent = root->parent;
    }
    delete root;
    return lChild;
  }
  // 2. Root is in range
  return root;
}

int main() {
  Tree<int> t;
  t.insert(8);
  t.insert(3);
  t.insert(10);
  t.insert(1);
  t.insert(6);
  t.insert(14);
  t.insert(4);
  t.insert(7);
  t.insert(13);
    
  t.print_head(t, cout);
    
  t.trim_BST(t.get_root(), 5, 13);
    
  t.print_head(t, cout);
    
  return 0;
}

