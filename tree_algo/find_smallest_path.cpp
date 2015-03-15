#include "bst.h"

/*
Problem: Given a Binary tree and two nodes. Need to find smallest path between them.

The algorithm is implemented in:
- deque<Node*> path_between_p_q(Node *root, Node *p, Node *q)
*/

template <class T>
typename Tree<T>::Node* Tree<T>::lca(Tree<T>::Node *root, Tree<T>::Node *p, Tree<T>::Node *q, deque<Tree<T>::Node*> &path, bool &both_found) {
  if(!root) {
    return NULL;
  } 
  
  path.push_back(root);
  
  if(root == p || root == q) {
    return root;
  }
  
  Tree<T>::Node *l = lca(root->left, p, q, path, both_found);
  Tree<T>::Node *r = lca(root->right, p, q, path, both_found);
    
  if(l && r) {
    both_found = true;
    return root;
  }
  else if(l) {
    return l;
  }
  path.pop_back();
  return r;
}

template <class T>
void Tree<T>::dfs(Tree<T>::Node *root, bool &found, Tree<T>::Node *find, deque<Node*> &path) {
  if(!root || found) {
    return;
  }
    
  if(!found) {
    path.push_front(root);
  }
    
  if(root == find) {
    found = true;
  }
    
  dfs(root->left, found, find, path);
  dfs(root->right, found, find, path);
    
  if(!found) {
    path.pop_front();
  }
}

template <class T>
deque<typename Tree<T>::Node*> Tree<T>::path_between_p_q(Tree<T>::Node *root, Tree<T>::Node *p, Tree<T>::Node *q) {
  deque<Tree<T>::Node*> path;
  bool both_found = false;

  Tree<T>::Node *r = lca(root, p, q, path, both_found);

  if(!both_found) {
    bool found = false;
      
    path.clear();
      
    if(r == p) {
      dfs(r, found, q, path);
    }
    else if(r == q) {
      dfs(r, found, p, path);
    }
  }
    
  return path;
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

  deque<Tree<int>::Node*> path = t4.path_between_p_q(t4.get_root(), t4.get_root()->left->left, t4.get_root()->right);

  for(int i = 0; i < path.size(); i++) {
      cout << path[i]->value << ' ';
  }
  return 0;
}

