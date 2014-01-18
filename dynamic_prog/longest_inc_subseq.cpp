#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
The longest increasing subsequence problem is to find a subsequence of a given sequence in
which the subsequence elements are in sorted order, lowest to highest, and in which the
subsequence is as long as possible.
Example: 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15, ...
a longest increasing subsequence is  0, 2, 6, 9, 13, 15.

Solution:
O(n^2)
*/

void replace_last(vector<vector<int>> &subseq, int val) {
	for (int i = subseq.size() - 1; i >= 0; i--) {
		int last_index = subseq[i].size() - 1;

		if (last_index > 0) {
			// if val is smaller than the last element of the subseq and
			// and if the new subseq is still increasing (val is larger than prev last)
			// replace last with val
			if (val < subseq[i][last_index] && val > subseq[i][last_index - 1]) {
				subseq[i][last_index] = val;
				break;
			}
		}
		else {
			// if val is smaller than the last element of the subseq
			// replace last with val
			if (val < subseq[i][last_index]) {
				subseq[i][last_index] = val;
				break;
			}
		}
	}
}

vector<int> find_longest_inc_subseq(vector<int> &vec) {
	vector<vector<int>> subseq;

	for (int i = 0; i < vec.size(); i++) {
		int size = subseq.size();

		if (size == 0) {
			vector<int> new_subseq;
			new_subseq.push_back(vec[i]);
			subseq.push_back(new_subseq);
		}
		// if vec[i] is larger than the back of the current longest subseq
		// duplicate current longest subseq and extend with vec[i]
		else if (vec[i] > subseq[size - 1].back()) {
			vector<int> new_subseq;
			new_subseq.insert(new_subseq.begin(), subseq[size - 1].begin(), subseq[size - 1].end());
			new_subseq.push_back(vec[i]);
			subseq.push_back(new_subseq);
		}
		// if vec[i] is smaller than the back of the current longest subseq
		// replace the last element if it is smaller than the current last element of the subseq
		// if its still increasing the subseq
		else if (vec[i] < subseq[size - 1].back()) {
			replace_last(subseq, vec[i]);
		}
	}

	return subseq[subseq.size() - 1];
}

int main() {
	// your code goes here

	vector<int> vec = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

	vector<int> longest_inc_subseq = find_longest_inc_subseq(vec);

	for_each(longest_inc_subseq.begin(), longest_inc_subseq.end(), [](int val) { cout << val << ' '; });

	return 0;
}