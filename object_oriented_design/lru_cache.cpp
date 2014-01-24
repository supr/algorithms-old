#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

/* Question:
Design an LRU cache with all the operations including getting the least recently
used item to be O(1)
*/

typedef struct entry {
	int key;
	int value;
	entry(int key_, int value_) : key(key_), value(value_) {}
}entry;

class LRU_Cache {
private:
	list<entry> l;
	unordered_map<int, decltype(l.begin())> ht;
	int cache_size;

private:
	void erase() {
		auto it_list = --l.end();
		ht.erase(it_list->key);
		l.pop_back();
	}

public:
	LRU_Cache(int cache_size_) : cache_size(cache_size_) {}

	void insert(int key, int value) {
		// if current size is larger than cache_size -> delete last recently used element
		int current_size = ht.size() + 1;
		if (current_size > cache_size) {
			erase();
		}

		auto it = ht.find(key);

		if (it != ht.end()) {
			l.erase(it->second);
			ht.erase(it);
		}

		l.push_front(entry(key, value));
		ht.insert(make_pair(key, l.begin()));
	}

	int find(int key) {
		auto it = ht.find(key);

		if (it != ht.end()) {
			l.push_front(entry(it->second->key, it->second->value));
			l.erase(it->second);
			it->second = l.begin();
			return it->second->value;
		}

		return 0;
	}

	bool contains(int key) {
		auto it = ht.find(key);

		return it != ht.end();
	}
};

int main() {
	// your code goes here

	LRU_Cache c(5);
	c.insert(1, 2);
	c.insert(2, 3);
	c.insert(3, 4);
	c.insert(4, 5);
	c.insert(5, 6);
	c.insert(5, 7);
	c.insert(6, 8);

	cout << c.find(1) << endl;
	cout << c.find(2) << endl;
	cout << c.find(5) << endl;

	cout << '\n';

	cout << c.contains(1) << endl;
	cout << c.contains(2) << endl;
	cout << c.contains(3) << endl;

	return 0;
}