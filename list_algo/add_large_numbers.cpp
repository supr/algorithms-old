#include <iostream>
using namespace std;

/*
Question:

Add 2 large numbers represented as linked lists and return the resulting linked list

For example:
Given 1->2->3 and 1->9->9->4, return 2->1->1->7
*/

typedef struct node {
	int value;
	node *next;
}node;

class llist {
private:
	node *first;
	node *last;
	int size;
	
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
		
		size++;
	}

	void insert_front(int val) {
		node *tmp = new node;
		tmp->value = val;
		tmp->next = NULL;

		if (first == NULL) {
			first = tmp;
			last = tmp;
		}
		else {
			node *first_old = first;
			first = tmp;
			first->next = first_old;
		}
		
		size++;
	}
	
	node *get_first() {
		return first;
	}
	
	int get_size() {
		return size;
	}

	void print() {
		node *tmp = first;

		while (tmp != NULL) {

			cout << tmp->value << ' ';

			tmp = tmp->next;
		}

		cout << '\n';
	}

	void reverse(node *curr, node *prev) {
		if(!curr) {
			return;
		}

		if(prev) {
			prev = prev->next;
		}		
		else if(curr != first) {
			prev = first;
		}

		reverse(curr->next, prev);
		
		if(curr == last) {
			first = last;
		}
		
		curr->next = prev;
		
		if(prev == NULL) {
			last = curr;
		} 
	}
	
	void add_large_numbers(llist &l1, llist &l2, llist &l3) {
		l1.reverse(l1.get_first(), NULL);
		l2.reverse(l2.get_first(), NULL);
		
		node *curr1 = l1.get_first();
		node *curr2 = l2.get_first();
		int carry = 0;
		
		while(curr1 || curr2) {
			int digit = 0;
			
			if(curr1 && curr2) {
				digit = carry + curr1->value + curr2->value;
				curr1 = curr1->next;
				curr2 = curr2->next;
			}
			else if(curr1) {
				digit = carry + curr1->value;
				curr1 = curr1->next;
			}
			else if(curr2) {
				digit = carry + curr2->value;
				curr2 = curr2->next;
			}
			
			l3.insert_front(digit % 10);
			
			carry = digit / 10;
		}
	}
};

int main() {
	// your code goes here

	llist l1;
	l1.insert(1);
	l1.insert(2);
	l1.insert(3);
	l1.print();
	
	llist l2;
	l2.insert(1);
	l2.insert(9);
	l2.insert(9);
	l2.insert(4);
	l2.print();
	
	llist l3;
	l1.add_large_numbers(l1, l2, l3);
	l3.print();

	return 0;
}
