#include "bst.h"

/*
Question: Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant
space solution?

The algorithm is implemented in:
- void recover_binary_tree(Node *root)
*/

template <class T>
void Tree<T>::recover_binary_tree_internal(Tree<T>::Node *root, Tree<T>::Node **prev, Tree<T>::Node **first_node_not_inorder) {
  if (!root) {
    return;
  }

  recover_binary_tree_internal(root->left, prev, first_node_not_inorder);

  if (*prev) {
    if (!(*first_node_not_inorder) && root->value < (*prev)->value) {
      *first_node_not_inorder = *prev;
    }
    else if (root->value < (*prev)->value) {
      std::swap((*first_node_not_inorder)->value, root->value);
    }
  }

  *prev = root;

  recover_binary_tree_internal(root->right, prev, first_node_not_inorder);
}

template <class T>
void Tree<T>::recover_binary_tree(Tree<T>::Node *root) {
  Tree<T>::Node *prev = NULL;
  Tree<T>::Node *first_node_not_inorder = NULL;
  recover_binary_tree_internal(root, &prev, &first_node_not_inorder);
}

int main() {
  Tree<int> t4;
  t4.insert(8);
  t4.insert(3);
  t4.insert(1);
  t4.insert(6);
  t4.insert(4);
  t4.insert(7);
  t4.insert(10);
  t4.insert(14);
  t4.insert(13);

  t4.print_head(t4, cout);

  swap(t4.get_root()->value, t4.get_root()->left->right->left->value);

  t4.print_head(t4, cout);

  t4.recover_binary_tree(t4.get_root());

  t4.print_head(t4, cout);

  return 0;
}