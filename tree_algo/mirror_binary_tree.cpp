#include "bst.h"

/*
Problem: Please implement a function which returns mirror of a binary tree.

Binary tree nodes are defined as:

struct BinaryTreeNode
{
int                    m_nValue;
BinaryTreeNode*        m_pLeft;
BinaryTreeNode*        m_pRight;
};

For example, the binary tree on the right of Figure 1 is the mirror of the left one.
      8               8     
   6    10        10    6
 5  7 9   11    11  9 7  5
 Figure 1       Figure 2

The algorithm is implemented in two different ways: 
- void mirror_tree_topdown(Node *root) 
- void mirror_tree_buttomup(Node *root)
*/

template <class T>
void Tree<T>::mirror_tree_topdown(Tree<T>::Node *root) {
  // we swap children as long root is not NULL
  if (root) {
    std::swap(root->left, root->right);
  }

  if (!root) {
    return;
  }

  mirror_tree_topdown(root->left);
  mirror_tree_topdown(root->right);
}

template <class T>
void Tree<T>::mirror_tree_bottomup(Tree<T>::Node *root) {
  if (!root) {
    return;
  }

  mirror_tree_bottomup(root->left);
  mirror_tree_bottomup(root->right);

  // we swap children as long root is not NULL
  if (root) {
    std::swap(root->left, root->right);
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

  t4.mirror_tree_topdown(t4.get_root());

  t4.print_head(t4, cout);

  t4.mirror_tree_bottomup(t4.get_root());

  t4.print_head(t4, cout);

  return 0;
}
