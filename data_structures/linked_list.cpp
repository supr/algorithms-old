// Linked List
/* A Linked List is a dynamic data structure storing a set of sequentially organized 
   items, so called nodes.
   Each node stores:
-	The data item 
-	The link to the next node in the list.
Usually we have two dummy nodes storing the first and last node of the list. The last node next node points to NULL.

   Advantages compared to arrays:
   	- easy growth and shrinking in size over lifetime
  	- high flexibility w.r.t. rearrangement of data items

   Runtime Complexity:
   Insert: O(1)
   Search: O(n) ... n is the length of the list
   Remove: O(n)
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

	node *get_first()
	{
		return first;
	}

	int count_nodes(node *n)
	{
		if (n == NULL)
			return 0;
		else {
			return count_nodes(n->next) + 1;
		}
	}

	void remove_dublicate() {
		std::unordered_set<int> dublicated_nodes;
		node *prev_node = first;
		node *tmp = NULL;

		if (first == NULL || first == last)
			return;

		for (node *lookup_node = first; lookup_node != NULL; lookup_node = lookup_node->next) {
			// lookup_node already exists in hash table --> we need to delete the lookup_node
			if (dublicated_nodes.find(lookup_node->value) != dublicated_nodes.end()) {
				prev_node->next = lookup_node->next;
				tmp = lookup_node;
				lookup_node = prev_node;
				delete(tmp);
			}
			else {
				dublicated_nodes.insert(lookup_node->value);

				if (lookup_node != first) {
					prev_node = prev_node->next;
				}
			}
		}
	}

	void print() {
		node *tmp = first;

		while (tmp != NULL) {

			cout << tmp->value << endl;

			tmp = tmp->next;
		}
	}

	node *return_nth_element(int n) {
		node *n_delayed = NULL;
		node *running_to_end = first;
		int count = 0;

		while (running_to_end != NULL) {
			running_to_end = running_to_end->next;
			count++;
			if (count == n) {
				n_delayed = first;
			}
			else if (count > n) {
				n_delayed = n_delayed->next;
			}
		}

		return n_delayed;
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

	void create_loop_to(int n) {
		node *tmp = first;

		if (first == NULL || first == last)
			return;

		while (tmp != NULL) {
			if (tmp->value == n) {
				last->next = tmp;
				return;
			}

			tmp = tmp->next;
		}
	}

	node *find_loop() {
		node *tmp1 = first;
		node *tmp2 = first;

		if (first == NULL || first == last)
			return NULL;

		// Find meeting point
		while (tmp1->next != NULL) {
			tmp1 = tmp1->next;
			tmp2 = tmp2->next->next;
			if (tmp1 == tmp2) {
				break;
			}
		}

		// Error check - there is no meeting point, and therefore no loop
		if (tmp2->next == NULL) {
			return NULL;
		}

		/* Move n1 to Head. Keep n2 at Meeting Point. Each are k steps
		/* from the Loop Start. If they move at the same pace, they must
		/* meet at Loop Start. */
		tmp1 = first;
		while (tmp1 != tmp2) {
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		// Now n2 points to the start of the loop.
		return tmp2;
	}
};