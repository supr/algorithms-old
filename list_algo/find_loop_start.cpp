#include <iostream>
using namespace std;

/* Question:
Given a circular linked list, implement an algorithm which returns the node at the
beginning of the loop.
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

	int count_nodes(node *n) {
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

			cout << tmp->value << endl;

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

	void create_loop_to(int to) {
		node *curr = first;

		if (first == NULL || first == last)
			return;

		while (curr != NULL) {
			if (curr->value == to) {
				last->next = curr;
				return;
			}

			curr = curr->next;
		}
	}

	int find_loop_start() {
		node *slow = first;
		node *fast = first;

		while (fast->next != NULL && fast->next->next != NULL) {
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast) {
				break;
			}
		}

		if (slow != NULL && fast != NULL) {
			slow = first;
		}

		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}

		if (slow != NULL) {
			return slow->value;
		}

		return -1;
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

	//l.print();

	l.create_loop_to(4);

	cout << l.find_loop_start() << endl;
}