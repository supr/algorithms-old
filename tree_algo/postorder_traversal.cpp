#include "bst.h"

/*
Question:
Given a binary search tree, print the elements post-order iterative and recursive.
Post-order
1. Traverse the left subtree.
2. Traverse the right subtree.
3. Visit the root.
The algorithm is implemented in:
- void postorder_traversal_recursive(Node *root);
- void postorder_traversal_iterative(Node *root);
- void postorder_traversal_iterative2(Node *root);
*/

template <class T>
void Tree<T>::postorder_traversal_recursive(Tree<T>::Node *root) {
  if(!root) {
    return;
  }

  postorder_traversal_iterative(root->left);
  postorder_traversal_iterative(root->right);

  cout << root->value << ' ';
}

template <class T>
void Tree<T>::postorder_traversal_iterative(Tree<T>::Node *root) {
  stack<Tree<T>::Node*> s;
  stack<Tree<T>::Node*> out;
  s.push(root);
    
  while(!s.empty()) {
    root = s.top();
    s.pop();
    out.push(root);
      
    if(root->left) {
      s.push(root->left);
    }
    if(root->right) {
      s.push(root->right);
    }
  }
    
  while(!out.empty()) {
    Tree<T>::Node *curr = out.top();
    out.pop();
      
    cout << curr->value << ' ';
  }
}

template <class T>
void Tree<T>::postorder_traversal_iterative2(Tree<T>::Node *root) {
  if (!root) return;
    
  stack<Tree<T>::Node*> s;
  s.push(root);
  Tree<T>::Node *prev = NULL;
  
  while (!s.empty()) {
    Tree<T>::Node *curr = s.top();
      
    // we are traversing down the tree
    if (!prev || prev->left == curr || prev->right == curr) {
      if (curr->left) {
        s.push(curr->left);
      }
      else if (curr->right) {
        s.push(curr->right);
      }
    } 
    // we are traversing up the tree from the left
    else if (curr->left == prev) {
      if (curr->right) {
        s.push(curr->right);
      }
    } 
    // we are traversing up the tree from the right
    else {
      cout << curr->value << " ";
      s.pop();
    }
      
    prev = curr; // record previously traversed node
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

  cout << "revursive: " << endl;
  t4.postorder_traversal_recursive(t4.get_root());
  cout << "\niterative: " << endl;
  t4.postorder_traversal_iterative(t4.get_root());
  cout << "\niterative2: " << endl;
  t4.postorder_traversal_iterative2(t4.get_root());

  return 0;
}