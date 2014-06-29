#include <iostream>
#include <unordered_set>
using namespace std;

/*
Question: Remove Duplicates from Unsorted List

Given a unsorted linked list, delete all nodes that have duplicate numbers, leaving only distinct
numbers from the original list.

For example,
Given 5->4->2->3->1->3->4, return 5->4->2->3->1
*/

typedef struct node_ {
  int value;
  node_ *next;
}node_;

class llist {
private:
  node_ *first;
  node_ *last;

public:
  llist() : first(NULL), last(NULL) {}

  void insert(int val) {
    node_ *tmp = new node_;
    tmp->value = val;
    tmp->next = NULL;

    if (first == NULL) {
      first = tmp;
      last = tmp;
    }
    else {
      last->next = tmp;
      last = tmp;
    }
  }

  node_ *get_first() {
    return first;
  }

  void print() {
    node_ *tmp = first;

    while (tmp != NULL) {

      cout << tmp->value << ' ';

      tmp = tmp->next;
    }

    cout << '\n';
  }
  
  void remove_duplicates() {
    node_ *prev = NULL;
    node_ *curr = first;
    unordered_set<int> hs;
    
    while(curr) {
      auto it = hs.find(curr->value);
      
      if(it != hs.end()) {
        node_ *tmp = curr;
        prev->next = curr->next;
        
        curr = curr->next;
        
        delete tmp;
      }
      else {
        hs.insert(curr->value);
        
        prev = curr;
        curr = curr->next;
      }
    }
  }
};

int main() {
  // your code goes here

  llist l;
  l.insert(5);
  l.insert(4);
  l.insert(2);
  l.insert(3);
  l.insert(1);
  l.insert(3);
  l.insert(4);

  l.print();

  l.remove_duplicates();

  l.print();

  llist l2;
  l2.insert(4);
  l2.insert(3);
  l2.insert(3);
  l2.insert(2);
  l2.insert(4);
  l2.insert(1);
  l2.insert(4);
  l2.insert(5);
  l2.insert(5);

  l2.print();

  l2.remove_duplicates();

  l2.print();

  return 0;
}