#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

/* Question:
Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
Your algorithm should run in O(n) complexity.
*/

int find_consec_seq_left(unordered_map<int, int> &ht, int num, vector<int> &indices) {
	unordered_map<int, int>::iterator it;

	do {
		it = ht.find(num - 1);

		if (it != ht.end()) {
			num--;
			indices.push_back(it->second);

			ht.erase(it);
		}
		else {
			break;
		}
	}while(it != ht.begin());

	return num;
}

int find_consec_seq_right(unordered_map<int, int> &ht, int num, vector<int> &indices) {
	unordered_map<int, int>::iterator it;

	do {
		it = ht.find(num + 1);

		if (it != ht.end()) {
			num++;
			indices.push_back(it->second);

			ht.erase(it);
		}
		else {
			break;
		}
	}while(it != ht.end());

	return num;
}

// insert all elements into a hash table, than iterate through the hash table and find beginning (min_index) and end (max_index) of each consecutive sequence
// during the search, delete the elements visited in the hash table
vector<int> find_long_consec_sequ(vector<int> &vec) {
	unordered_map<int, int> ht;
	int consec_seq_max = 0;
	vector<int> consec_seq_max_indices;

	for (int i = 0; i < vec.size(); i++) {
		ht.insert(make_pair(vec[i], i));
	}

	while (!ht.empty()) {
		auto it = ht.begin();
		int num = it->first;

		vector<int> indices_l;
		int min_index = find_consec_seq_left(ht, num, indices_l);
		vector<int> indices_r;
		int max_inde = find_consec_seq_right(ht, num, indices_r);

		if ((max_index - min_index + 1) > consec_seq_max) {
			consec_seq_max = max_index - min_index + 1;

			consec_seq_max_indices.insert(consec_seq_max_indices.begin(), indices_l.begin(), indices_l.end());
			consec_seq_max_indices.push_back(it->second);
			consec_seq_max_indices.insert(consec_seq_max_indices.begin(), indices_r.begin(), indices_r.end());
		}

		ht.erase(it);
	}

	return consec_seq_max_indices;
}

int main() {
	// your code goes here

	vector<int> vec = { 100, 4, 200, 1, 3, 2 };
	vector<int> indices = find_long_consec_sequ(vec);

	for_each(indices.begin(), indices.end(), [&](int index){ cout << vec[index] << ' '; });

	return 0;
}