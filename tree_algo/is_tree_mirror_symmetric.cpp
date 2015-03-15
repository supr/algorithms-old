#include "bst.h"
using namespace std;

/*
Question: Implement a function to verify whether a binary tree is symmetrical. A tree 
is symmetrical if its mirror image looks the same as the tree itself.
The algorithm is implemented in:
- bool is_tree_symmetrical(Tree<T>::Node *root)
*/

template <class T>
typename Tree<T>::Node* Tree<T>::get_most_left_node(Tree<T>::Node *root) {
  Tree<T>::Node *n = root;

  while (n->left) {
    n = n->left;
  }

  return n;
}

template <class T>
typename Tree<T>::Node* Tree<T>::in_order_iterator(Tree<T>::Node *root) {
  Tree<T>::Node *n = root;

  if (n->left) {
    n = get_most_left_node(n->right);
  }
  else {
    Tree<T>::Node *prev = n;

    while (n) {
      if (n->left == prev) {
        break;
      }

      prev = n;
      n = n->parent;
    }
  }

  return n;
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_most_right_node(Tree<T>::Node *root) {
  Tree<T>::Node *n = root;

  while (n->right) {
    n = n->right;
  }

  return n;
}

template <class T>
typename Tree<T>::Node* Tree<T>::in_order_iterator_mirrored(Tree<T>::Node *root) {
  Tree<T>::Node *n = root;

  if (n->right) {
    n = get_most_right_node(n->left);
  }
  else {
    Tree<T>::Node *prev = n;

    while (n) {
      if (n->right == prev) {
        break;
      }

      prev = n;
      n = n->parent;
    }
  }

  return n;
}

template <class T>
// do a inorder and a mirrored inorder traversal
bool Tree<T>::is_tree_symmetrical(Tree<T>::Node *root) {
  Tree<T>::Node *inorder_node = get_most_left_node(root);
  Tree<T>::Node *inorder_node_mirrored = get_most_right_node(root);

  while (inorder_node != get_root() && inorder_node_mirrored != get_root()) {
    inorder_node = in_order_iterator(inorder_node);
    inorder_node_mirrored = in_order_iterator_mirrored(inorder_node_mirrored);

    if (inorder_node->value != inorder_node_mirrored->value) {
      break;
    }
  }

  return inorder_node == inorder_node_mirrored;
}

template <class T>
bool Tree<T>::is_mirror_tree_recursive(Tree<T>::Node *LP, Tree<T>::Node *RP) {
  bool result = false;
    
  // If both null then true
  if (LP == NULL && RP == NULL) { 
    result = true;
  } 
    
  // check that data is equal and then recurse
  if (LP != NULL && RP != NULL) {
    result = LP->value == RP->value && 
             is_mirror_tree_recursive( LP->left, RP->right ) && 
             is_mirror_tree_recursive( LP->right, RP->left );
  }
    
  return result;
}

template <class T>
bool Tree<T>::is_mirror_tree_iterative(Tree<T>::Node *root)  {
  /// use single queue
  if(!root) return true;
  queue<Tree<T>::Node*> q;
    
  q.push(root->left);
  q.push(root->right);
    
  Tree<T>::Node *l, *r;
  while(!q.empty()) {
    l = q.front();
    q.pop();
    r = q.front();
    q.pop();
    if(l==NULL && r==NULL) continue;
    if(l==NULL || r==NULL || l->value != r->value) return false;
    q.push(l->left);
    q.push(r->right);
    q.push(l->right);
    q.push(r->left);
  }

  return true;
}

int main() {
  Tree<int> t4;
  t4.insert(8);
  t4.insert(6);
  t4.insert(5);
  t4.insert(7);
  t4.insert(12);
  t4.insert(11);
  t4.insert(13);

  t4.print_head(t4, cout);

  cout << ((t4.is_mirror_tree_iterative(t4.get_root())) ? ("Tree is symmetrical") : ("Tree is not symmetrical")) << endl;
  cout << ((t4.is_mirror_tree_recursive(t4.get_root(), t4.get_root())) ? ("Tree is symmetrical") : ("Tree is not symmetrical")) << endl;

  cout << '\n';

  // modify the tree to be a symmetrical tree
  t4.get_root()->right->value = 6;
  t4.get_root()->right->left->value = 7;
  t4.get_root()->right->right->value = 5;

  t4.print_head(t4, cout);

  cout << ((t4.is_mirror_tree_iterative(t4.get_root())) ? ("Tree is symmetrical") : ("Tree is not symmetrical")) << endl;
  cout << ((t4.is_mirror_tree_recursive(t4.get_root(), t4.get_root())) ? ("Tree is symmetrical") : ("Tree is not symmetrical")) << endl;

  return 0;
}