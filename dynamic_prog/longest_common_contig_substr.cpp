#include <iostream>
#include <string>
#include <locale>
#include <vector>
using namespace std;

/* Question:
Find the longest intersection between two strings
Find the longest common contiguous substring of two given strings

longest_common_contig_substr1  Time: O(n * m), Space: O(n^2)  ... based on trie
longest_common_contig_substr2: Time: O(n * m^2), Space: O(1)
longest_common_contig_substr3: Time: O(n * m), Space: O(m * n) ... based on dynamic programming

A suffix tree based solution would run in O(n + m)
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
		int counter = 0;
		
		for (int i = 0; i < key.size(); i++) {
			char k = tolower(key[i]) - 'a';

			if (tmp->next[k]) {
				counter++;
				tmp = tmp->next[k];
			}
			else {
				return counter; //-1; // key not found
			}
		}

		if (!tmp && tmp->value < 0) {
			return -1;
		}

		return counter;//tmp->value;
	}

	// delete key and corresponding value
	void del(string key) {
		bool node_in_use = false;
		delete_key(root, root, key, 0, node_in_use);
	}
};

string longest_common_contig_substr1(const string &str1, const string &str2) {
	trie<char> t;
	int max_count = 0;
	int count = 0;
	int index = 0;
	
	for(int i = 0; i < str1.size(); i++) {
		t.put(str1.substr(i, str1.size() - i), 1);
	}
	
	for(int i = 0; i < str2.size(); i++) {
		count = t.get(str2.substr(i, str2.size() - i));
		
		if(count > max_count) {
			max_count = count;
			index = i;
		}
	}
	
	return str2.substr(index, max_count);
}

string longest_common_contig_substr2(const string &str1, const string &str2) {
	int index_start = 0;
	int index_end = 0;
	int count = 0;
	int count_max = 0;

	for(int i = 0; i < str1.size(); i++) {
		int k = i;

		for(int j = 0; j < str2.size(); j++) {
			if(k >= str1.size()) {
				break;
			}
			
			if(str1[k] == str2[j]) {
				if(count > count_max) {
					count_max = count;
					index_start = i;
					index_end = k;
				}
				
				count++;
				k++;
			}
			else {
				count = 0;
			}
		}
	}

	return str1.substr(index_start, index_end - index_start + 1);
}

string longest_common_contig_substr3(const string &str1, const string &str2) {
  int this_subs_begin = 0;
  int last_subs_begin = 0;
  int m = str1.size();
  int n = str2.size();
  vector<vector<int>> num;
  num.resize(m, vector<int>(n, 0));
  int maxlen = 0;
  string out;
  
  for(int i = 0; i < m; i++) {
  	for(int j = 0;j < n;j++) {
    		if(str1[i] != str2[j]) {
     			num[i][j] = 0;
    		}
    		else {
     			if(i == 0 || j == 0) {
      				num[i][j] = 1;
     			}
     			else {
      				num[i][j] = num[i-1][j-1] + 1;
     			}
     		
     			if(num[i][j] > maxlen) {
      				maxlen = num[i][j];
      				// generate substring from str1 => i
      				this_subs_begin = (i + 1) - maxlen;
      
      				// if the current LCS is the same as the last time
      				if(this_subs_begin == last_subs_begin) {
       					out += str1[i];
      				}
      				else {
      					// this resets the out string if a different LCS is found
       					last_subs_begin = this_subs_begin;
       					out.clear();
       					out += str1.substr(this_subs_begin, i);
      				}
      			}
    		}
   	}
  }
  
  return out;
}
 
int main() {
	// your code goes here
	
	string str1 = "hello";
	string str2 = "bella";
	
	cout << longest_common_contig_substr1(str1, str2) << endl;
	cout << longest_common_contig_substr2(str1, str2) << endl;
	cout << longest_common_contig_substr3(str1, str2) << endl;
	
	return 0;
}
