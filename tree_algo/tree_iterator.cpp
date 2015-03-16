#include "bst.h"

/*
Question:
Given a binary search tree, implement a inorder iterator class

Inorder:
1. Traverse the left subtree.
2. Visit the root.
3. Traverse the right subtree.
*/

template<class T>
class TreeContainer : public Tree<T> {
public:
  class tree_iterator {
  private:
    Tree<T> *ptree;
    typename Tree<T>::Node *curr;
    typename Tree<T>::Node *prev;

  public:
    tree_iterator(Tree<T> *ptree_): ptree(ptree_), curr(nullptr), prev(nullptr) {}

    bool operator== (const tree_iterator &it) {
      return this->get_curr() == it.get_curr();
    }
    
    bool operator!= (const tree_iterator &it) {
      return this->get_curr() != it.get_curr();
    }
    
    typename Tree<T>::Node operator* () {
      return *this->get_curr();
    }

    typename Tree<T>::Node *operator-> () {
      return this->get_curr();
    }
    
    // inorder_traversal
    void operator++(int) {
      if(curr) {
        typename Tree<T>::Node *tmp;
      
        // Found right children -> return 1st inorder node on right
        if (!curr->parent || curr->right) {
          tmp = leftMostChild(curr->right);
        } 
        else {
          // Go up until we are on left instead of right (case 2b)
          while ((tmp = curr->parent)) {
            if (tmp->left == curr) {
              break;
            }
            curr = tmp;
          }
        }
        curr = tmp;
      }
    }

    typename Tree<T>::Node *get_curr() const {
      return curr;
    }
  
    typename Tree<T>::Node *get_root() {
      return ptree->get_root();
    }
  
    void tree_iterator_begin(typename Tree<T>::Node *start) {
      prev = nullptr;
      curr = start;
    }
  
    void tree_iterator_end() {
      curr = nullptr;
    }

    typename Tree<T>::Node *leftMostChild(typename Tree<T>::Node *e) {
      if (!e) return nullptr;
      
      while (e->left) {
        e = e->left;
      }
        
      return e;
    }
  };

public:
  tree_iterator begin() {
    tree_iterator it(this);
    typename Tree<T>::Node *start = it.leftMostChild(this->root);
    it.tree_iterator_begin(start);
    return it;
  }
    
  tree_iterator end() {
    tree_iterator it(this);
    it.tree_iterator_end();
    return it;
  }
};

int main() {
  // your code goes here
  
  TreeContainer<int> t;
  t.insert(10);
  t.insert(5);
  t.insert(12);
  t.insert(4);
  t.insert(3);
  t.insert(2);
  t.insert(7);
  t.insert(14);
  
  t.print_head(t, cout);
  
  for(TreeContainer<int>::tree_iterator itr = t.begin(); itr != t.end(); itr++) {
    cout << itr->value << ' ';
  }
  
  return 0;
}