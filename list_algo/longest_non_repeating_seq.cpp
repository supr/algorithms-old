#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

/* Question:
Given a circular linked list, with a loop from the end to the beginning.
Return the longest non repeating sequence of the list.

Example 1:
a->b->c->d->e->a->e
^-----------------|

would result in:
a->b->c->d->e
or 
e->a->b->c->d
or
b->c->d->e->a

Example 2:
a->b>->a->d->g->h->z

would result in:
^------------------|
a->b
b->a->d->g->h->z
a->d->g->g->z
*/

typedef struct node {
  char value;
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

  int count_nodes(node *n) {
    if (n == NULL) {
      return 0;
    }
    else {
      return count_nodes(n->next) + 1;
    }
  }

  void print(node *start) {
    node *tmp = start;

    while (tmp != NULL) {

      cout << tmp->value << ' ';

      tmp = tmp->next;
    }
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

  void create_loop() {
    last->next = first;
  }
  
  node *get_non_repeating(node *start) {
      std::unordered_set<char> ht;
      node *curr = start;
      node *curr2 = start;
      node *longest_start = NULL;
      unsigned int longest_match = 0;
      unsigned int match_count = 0;
      
      // O(n^2)
      while(curr->next != start) {
          curr2 = curr; // initialize curr2
          match_count = 0; // reset curr_match
          ht.clear();
          
          while(curr2->next != curr) {
              auto it = ht.find(curr2->value);
              bool loop_exit = false;
              
              // if character does not exist in hash table, increment curr_match
              if(it == ht.end()) {    
                  match_count++;
                  ht.insert(curr2->value);  
              }
              // if it does not exist in ht, set exit flag to true
              else {
                  match_count = 0;
                  loop_exit = true;
              }
              
              // if curr_match larger than longest_match, update longest_start pointer
              if(match_count > longest_match) {
                  longest_match = match_count;
                  longest_start = curr;        
              }   
              
              if(loop_exit) {
                  break;
              }
          
              curr2 = curr2->next;  
          }
              
          curr = curr->next;  
      }
      
      // O(n)
      // set the next pointer of the non prep seq to zero
      node *non_rep = longest_start;
      unsigned int i = 0;
      
      while(non_rep->next != longest_start) {
          if(i == longest_match-1) {
              non_rep->next = NULL;  
              break;
          }
          
          i++;
          non_rep = non_rep->next;
      }
      
      return longest_start;
   }
};

int main() {
  llist l;
  l.insert('a');
  l.insert('b');
  l.insert('a');
  l.insert('d');
  l.insert('g');
  l.insert('h');
  l.insert('z');
  
  l.create_loop();

  node *start = l.get_non_repeating(l.get_first());
  
  l.print(start);
  
  return 0;
}