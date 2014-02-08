#include <iostream>
#include <string>
#include <locale>
#include <vector>
using namespace std;

/* Question:
Implemented a trie data structure.

The standard trie for a set of strings S is an ordered tree such that:
- each node but the root is labeled with a character
- the children of a node are alphabetically ordered
- the paths from the external nodes to the root yield the strings of S

Time Complexity:
 - Find: alphabet size (26) * length of the string
 - Insert: alphabet size (26) * length of the string
 - Delete: alphabet size (26) * length of the string

Space Complexity:
 - total size of the strings

Suffix trie: compress chains of redudant nodes
*/

const int ALPHABET_SIZE = 26;

template<class T>
class node {
public:
	T value;
	node *next[ALPHABET_SIZE];
	bool is_end;
	node() : value(-1), is_end(false) {}
};

template<class T>
class trie
{
private:
	node<T> *root;

	void init() {
		root = get_node();
	}

	node<T> *get_node(int key = -1) {
		node<T> *n = new node<T>();

		for (int j = 0; j < ALPHABET_SIZE; j++) {
			n->next[j] = NULL;
		}

		return n;
	}

	bool can_delete_node(node<T> *n) {
		if (!n->is_end || (!n->value < 0)) {
			return false;
		}

		return true;
	}

	bool is_root(node<T> *n) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (n == root->next[i]) {
				return true;
			}
		}

		return false;
	}

	void set_node_is_end(node<T> *n, int k) {
		bool is_used = false;

		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if (i != k && n->next[i]) {
				is_used = true;
			}
		}

		if (!is_used) {
			n->is_end = true;
		}
	}

	void delete_key(node<T> *n, string key, int index) {
		if (index <= key.size()) {
			if (index < key.size()) {
				char k = tolower(key[index]) - 'a';

				if (n->next[k]) {
					set_node_is_end(n, k);
					delete_key(n->next[k], key, ++index);
				}
			}
			else {
				// key/value is not used any more
				n->value = -1;
			}
		}

		// check if is_end
		if (!is_root(n) && can_delete_node(n)) {
			for (int i = 0; i < ALPHABET_SIZE; i++) {
				delete n->next[i];
			}
		}
	}

public:
	trie() {
		init();
	}

	// insert
	void put(string key, T value) {
		node<T> *tmp = root;

		for (int i = 0; i < key.size(); i++) {
			char k = tolower(key[i]) - 'a';

			if (!tmp->next[k]) {
				tmp->next[k] = get_node(k);
			}

			tmp->is_end = false;
			tmp = tmp->next[k];
		}

		tmp->is_end = true;
		tmp->value = value;
	}

	// return value with given key
	T get(string key) {
		node<T> *tmp = root;

		for (int i = 0; i < key.size(); i++) {
			char k = tolower(key[i]) - 'a';

			if (tmp->next[k]) {
				tmp = tmp->next[k];
			}
			else {
				return -1; // key not found
			}
		}

		if (!tmp && tmp->value < 0) {
			return -1;
		}

		return tmp->value;
	}

	// delete key and corresponding value
	void del(string key) {
		delete_key(root, key, 0);
	}
};

int main() {
	return 0;
}