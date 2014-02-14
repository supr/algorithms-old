#include <iostream>
using namespace std;

/*
Question:
write a program to reverse a doubly Linked list
*/

typedef struct node {
	int value;
	node *next;
	node *prev;
	node(int value_) : value(value_), next(NULL), prev(NULL) {}
}node;

class llist {
private:
	node *first;
	node *last;

public:
	llist() : first(NULL), last(NULL) {}

	void insert(int val) {
		node *tmp = new node(val);

		if (first == NULL) {
			first = tmp;
			last = tmp;
		}
		else {
			tmp->prev = last;
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

	node *reverse_list_internal(node *curr) {
		if (curr->next == NULL) {
			first = curr;
			curr->prev = NULL;
			return curr;
		}

		node *prev_node = reverse_list_internal(curr->next);

		if (curr->prev != NULL) {
			prev_node->next = curr;
			curr->prev = prev_node;
		}
		else {
			prev_node->next = curr;
			curr->prev = prev_node;
			curr->next = NULL;
			last = curr;
		}

		return curr;
	}

	void reverse_doubly_linked_list() {
		reverse_list_internal(first);
	}
};

int main() {
	// your code goes here

	llist l;
	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.insert(3);
	l.insert(4);
	l.insert(4);
	l.insert(5);

	l.print();

	l.reverse_doubly_linked_list();

	l.print();

	return 0;
}
