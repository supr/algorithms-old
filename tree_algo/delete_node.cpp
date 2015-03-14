#include "bst.h"
using namespace std;

/*
Question: Delete all the nodes of a Binary Search Treee

The algorithm is implemented in two different ways:
- void delete_all_nodes()
*/

template <class T>
typename Tree<T>::Node* Tree<T>::get_parent(Tree<T>::Node *curr, Tree<T>::Node *to_find) {
  if(!curr) {
    return NULL;
  }

  if(to_find == root) {
    return NULL;
  }
  else if(curr->left == to_find || curr->right == to_find) {
    return curr;
  }

  return get_parent(curr->left, to_find);
  return get_parent(curr->right, to_find);
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_most_left_node(Tree<T>::Node *curr) {
  Tree<T>::Node *prev = NULL;

  while(curr) {
    prev = curr;

    if(curr->left) {
      curr = curr->left;
    }
    else if(curr->right) {
      curr = curr->right;
    }
    else {
      break;
    }
  }

  return prev;
}

template <class T>
void Tree<T>::delete_node(Tree<T>::Node *curr) {
  if(!curr) {
    return;
  }
    
  // case 3
  if(curr->left && curr->right) {
    Node *next_node_inorder = get_most_left_node(curr->right);
    std::swap(next_node_inorder->value, curr->value);  
      
    delete_node(next_node_inorder);
  }
  // case 1, case 2
  else {
    Tree<T>::Node *parent = get_parent(root, curr);
    
    // if the node to delete has a parent, we need to change the parents child pointer
    if(parent) {
      if(parent->left == curr) {
        parent->left = curr->left;
      }
      else {
        parent->right = curr->right;
      }

      delete curr;
    }
    // if the node to delete has no parent (node to delete == root), we set a new root node
    else {
      Tree<T>::Node *tmp = curr;

      if(curr->left) {
        root = curr->left;
        root->parent = NULL;
      }
      else if(curr->right) {
        root = curr->right;
        root->parent = NULL;
      }
      else {
        root = NULL;
      }

      delete tmp;
    }
  }
}

int main() {
  Tree<int> t;
  t.insert(10);
  t.insert(5);
  t.insert(12);
  t.insert(4);
  t.insert(7);

  t.print_head(t, cout);
  
  t.delete_node(t.get_root());
  t.delete_node(t.get_root());

  t.print_head(t, cout);
  
  return 0;
}