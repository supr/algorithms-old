#include "bst.h"
using namespace std;

/*
Problem: Given a binary tree node, return the next node postorder.

The algorithm is implemented in:
- Node *get_next_node_postorder(Node *current)
- Node *get_next_node_ipostorder2(Node *current)

Post-order
1. Traverse the left subtree.
2. Traverse the right subtree.
3. Visit the root.

Time complexity:
both algorithms run in O(h) where h is height of tree.
*/

template <class T>
typename Tree<T>::Node* Tree<T>::get_next_node_postorder(Tree<T>::Node *root, Tree<T>::Node *curr) {
  if(root == NULL)
    return NULL;

  if(root->left != NULL && root->left->value == curr->value) {
    Tree<T>::Node *temp = find_next_node(root->right);
      
    if(temp == NULL)
      return root;
    else 
      return temp;
  }
  else if(root->right != NULL && root->right->value == curr->value) {
    return root;
  }

  Tree<T>::Node *left = get_next_node_postorder(root->left, curr);

  if(left!= NULL)
    return left;
  else return get_next_node_postorder(root->right, curr);
}

template <class T>
typename Tree<T>::Node* Tree<T>::find_next_node(Tree<T>::Node *root) {
  if(root == NULL)
    return NULL;

  if(is_leaf(root) == true)
    return root;

  Tree<T>::Node *left = find_next_node(root->left);
    
  if(left != NULL)
    return left;
  else 
    return find_next_node(root->right);
}

template <class T>
bool Tree<T>::is_leaf(Tree<T>::Node *root) {
  if(root->left == NULL && root->right == NULL)
    return true;
  return false;
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_next_node_postorder2(Tree<T>::Node *root, Tree<T>::Node *curr) {
  return postorderSuccessor_internal2(root,curr,NULL,NULL,root);
}

template <class T>
typename Tree<T>::Node* Tree<T>::postorderSuccessor_internal2(Tree<T>::Node *root, Tree<T>::Node *curr, Tree<T>::Node *direct_parent, Tree<T>::Node *parent, Tree<T>::Node *treeroot) {
  //Case 1: If current root is NULL, then succ(current root) is NULL.
  if (root == NULL)
    return 0;

  //Case 2: If current root is target node for which we are looking for successor.
  if (root->value == curr->value) {
    //Case 2.1: If current root is the root of the tree, succ(current root) is undefined.
    if(root == treeroot)
      return NULL;

    //Case 2.2: Otherwise, if current root is a right child, succ(current root) is parent(current root).
    else if(direct_parent != NULL && direct_parent->right==root)
      return direct_parent;

    //Case 2.3: Otherwise current root is a left child and the following applies:
    //Case 2.3.1: If u has a right sibling, r, succ(current root) is the leftmost leaf in r's sub-tree
    else if(direct_parent != NULL && direct_parent->left==root && direct_parent->right!=NULL)
      return get_most_left_node(direct_parent->right);

    //Case 2.3.2: Otherwise succ(current root) is parent(current root).
    else if(direct_parent != NULL && direct_parent->left==root && direct_parent->right==NULL)
      return direct_parent;

    //Case 2.3.3: If none of above applies, then succ(current root) doesn't exist.
    else
      return NULL;
  }

  //Case 3: Current root is not the target node for which we are looking successor.
  else {
    //Case 3.1: Search target node and its successor in left side of tree recursively, and return if found.
    Tree<T>::Node *left=postorderSuccessor_internal2(root->left,curr,root,root,treeroot);

    if (left)
      return left;

    //Case 3.2: Search target node and its successor in right side of tree recursively, and return.
    return postorderSuccessor_internal2(root->right,curr,root,parent,treeroot);
  }
}

template <class T>
typename Tree<T>::Node* Tree<T>::get_most_left_node(Tree<T>::Node *root) {
  while (root->left || root->right) {
    if(root->left) root=root->left;
      else root=root->right;
    }

  return root;
}

template <class T>
typename Tree<T>::Node* Tree<T>::postorder_successor(Tree<T>::Node *curr) {
  Tree<T>::Node *next_node = NULL;
    
  if(!curr) {
    return NULL;
  }
    
  if(!curr->left && !curr->right) {
    Tree<T>::Node *prev = curr;
 
    curr = curr->parent;
      
    if(curr->left == prev) {
      if(curr->right) {
        next_node = get_most_left_node(curr->right);
      }
      else {
        next_node = curr;
      }
    }
    else {
      next_node = curr;
    }
  }
  else if(curr->left && curr->right) {
    if(curr == root) {
      return NULL;
    }
    else if(root->right) {
      next_node = get_most_left_node(root->right);
    }
    else {
      next_node = curr->parent;
    }
  }
  else if(curr->left) {
    Tree<T>::Node *prev = curr->parent;
      
    if(prev) {
      if(prev->right) {
        next_node = prev->right;
      }
      else {
        next_node = prev;
      }
    }
  }
  else if(curr->right) {
    next_node = curr->parent;
  }
    
  return next_node;
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
    n = t4.get_next_node_postorder(t4.get_root(), n);
  }

  cout << '\n';
  
  n = t4.get_most_left_node(t4.get_root());
  while (n) {
    cout << n->value << ' ';
    n = t4.get_next_node_postorder2(t4.get_root(), n);
  }


  cout << '\n';
  
  n = t4.get_most_left_node(t4.get_root());
  while (n) {
    cout << n->value << ' ';
    n = t4.postorder_successor(n);
  }

  return 0;
}
