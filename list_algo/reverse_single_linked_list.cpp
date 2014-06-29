#include <iostream>
using namespace std;

/*
Question: Reverse a single linked list.

eg 1->2->3->4->5->6->7->8->9->10->11
answer must be [10->9->8->7->6->5->4->3->2->1]
*/

typedef struct node {
  int value;
  node *next;
}node;

class llist {
private:
  node *first;
  node *last;

public:
  llist() : first(NULL), last(NULL) {}

  void insert(int val) {
    node *tmp = new node;
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

  node *get_first() {
    return first;
  }

  int count_nodes(struct node *n) {
    if (n == NULL) {
      return 0;
    }
    else {
      return count_nodes(n->next) + 1;
    }
  }

  void print() {
    node *tmp = first;

    while (tmp != NULL) {

      cout << tmp->value << ' ';

      tmp = tmp->next;
    }

    cout << '\n';
  }

  void delete_node(node *n) {
    node *tmp = first;

    while (tmp != NULL) {

      if (tmp->next == n) {
        tmp->next = tmp->next->next;

        delete(n);
      }
      else {
        tmp = tmp->next;
      }
    }
  }

  node *reverse_internal(node *curr) {
      if(!curr) { 
          return NULL;
      }
      
      node *prev = reverse_internal(curr->next);
      if(prev) {
          if(!first) {
              first = prev;
          }
          
          prev->next = curr;
      }
      
      return curr;
  }
  
  void reverse() {
      node *curr = first;
      first = NULL;
      last = reverse_internal(curr);
      last->next = NULL;
  }
};

int main() {

  llist l;
  l.insert(1);
  l.insert(2);
  l.insert(3);
  l.insert(4);
  l.insert(5);
  l.insert(6);
  l.insert(7);
  l.insert(8);
  l.insert(9);

  l.print();

  l.reverse();

  l.print();

  return 0;
}