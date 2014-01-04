#include <iostream>
using namespace std;

/*
Question: Remove Duplicates from Sorted List

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct
numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
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

	int count_nodes(struct node_ *n) {
		if (n == NULL) {
			return 0;
		}
		else {
			return count_nodes(n->next) + 1;
		}
	}

	void print() {
		node_ *tmp = first;

		while (tmp != NULL) {

			cout << tmp->value << ' ';

			tmp = tmp->next;
		}

		cout << '\n';
	}

	void delete_node(node_ *n) {
		node_ *tmp = first;

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
		node_ *curr = first;
		node_ *prev = NULL;

		while (curr) {
			if (prev && curr->value == prev->value) {
				node_ *delete_node = curr;

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

	l.remove_duplicates();

	l.print();

	llist l2;
	l2.insert(1);
	l2.insert(2);
	l2.insert(3);
	l2.insert(3);
	l2.insert(4);
	l2.insert(4);
	l2.insert(4);
	l2.insert(5);
	l2.insert(5);

	l2.print();

	l2.remove_duplicates();

	l2.print();

	return 0;
}