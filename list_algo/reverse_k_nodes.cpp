#include <iostream>
using namespace std;

/*
Question: Reverse k nodes in a linked list.

eg 1->2->3->4->5->6->7->8->9->10->11 [k=3]
answer must be [3->2->1->6->5->4->9->8->7->11->10]
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

  void remove_duplicates() {
    node *curr = first;
    node *prev = NULL;

    while (curr) {
      if (prev && curr->value == prev->value) {
        node *delete_node = curr;

        while (curr && curr->value == prev->value) {
          delete_node = curr;
          curr = curr->next;
          delete(delete_node);
        }

        prev->next = curr;
      }

      if (curr) {
        prev = curr;
        curr = curr->next;
      }
    }
  }

  node *reverse(node *curr, node *&curr_first, node *&next_start, int &count, const int max_count) {
    if(!curr->next || count == max_count - 1) {
      curr_first = curr;
      next_start = curr->next;
      return curr;
    }
    
    node *curr_next = reverse(curr->next, curr_first, next_start, ++count, max_count);
    if(curr_next) {
      curr_next->next = curr; 
    }
    
    return curr;
  }

  void reverse_ll(int k) {
    node *next_start = NULL;
    node *start = first;
    node *curr_first = NULL;
    node *prev_last = NULL;
    node *curr_last = NULL;
    
    while(true) {
      int count = 0;

      curr_last = reverse(start, curr_first, next_start, count, k);

      // update start for next reverse call
      if(next_start) {
        start = next_start;
      }
      
      if(prev_last) {
        prev_last->next = curr_first;
      }
      else {
        first = curr_first;
      }
      prev_last = curr_last;
      
      if(!next_start) {
        break;
      }
    }
    
    prev_last->next = next_start;
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

  l.reverse_ll(8);

  l.print();

  return 0;
}