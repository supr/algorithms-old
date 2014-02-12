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
			if (n == root) {
				return true;
			}
		}

		return false;
	}

	bool set_node_is_end(node<T> *n, int k) {
		bool is_used = false;

		for (int i = 0; i < ALPHABET_SIZE; i++) {
			if ((i != k && n->next[i]) || n->value != -1) {
				is_used = true;
				break;
			}
		}

 		if (!is_used) {
			n->is_end = true;
		}

		return is_used;
	}
	
	void delete_key(node<T> *curr, node<T> *prev, string key, int index, bool &node_in_use) {
		bool is_used = false;

		if (index <= key.size()) {
			if (index < key.size()) {
				char k = tolower(key[index]) - 'a';

				if (curr->next[k]) {
					is_used = set_node_is_end(curr, k);
					delete_key(curr->next[k], curr, key, ++index, node_in_use);
				}
			}
			else {
				// key/value is not used any more
				curr->value = -1;
			}
		}

		if (is_used) {
			node_in_use = is_used;
		}

		if (!node_in_use && !is_root(curr) && can_delete_node(curr)) {
			if (prev) {
				for (int j = 0; j < ALPHABET_SIZE; j++) {
					if (prev->next[j] == curr) {
						prev->next[j] = NULL;
						break;
					}
				}
			}

			delete curr;
			curr = NULL;
		}
	}

public:
	trie() {
		root = get_node();
	}

	~trie() {
		delete root;
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
		bool node_in_use = false;
		delete_key(root, root, key, 0, node_in_use);
	}
};

int main() {
	trie<int> t;

	vector<pair<string, int>> vec = { { "sea", 6 },
									  { "sells", 1 },
									  { "she", 0 },
									  { "shells", 3 },
									  { "shore", 7 },
									  { "the", 5 } };

	for (int i = 0; i < vec.size(); i++) {
		t.put(vec[i].first, vec[i].second);
	}

	for (int i = 0; i < vec.size(); i++) {
		cout << t.get(vec[i].first) << ' ';
	}

	cout << '\n';

	for (int i = 0; i < vec.size(); i++) {
		t.del(vec[i].first);
	}

	for (int i = 0; i < vec.size(); i++) {
		cout << t.get(vec[i].first) << ' ';
	}

	cout << '\n';

	for (int i = 0; i < vec.size(); i++) {
		t.put(vec[i].first, vec[i].second);
	}

	for (int i = 0; i < vec.size(); i++) {
		cout << t.get(vec[i].first) << ' ';
	}

	return 0;
}