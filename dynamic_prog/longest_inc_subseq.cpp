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

// Finds longest increasing subsequence...strictly increasing subsequence.O(n log k) algorithm. * /
// explain: http://www.algorithmist.com/index.php/Longest_Increasing_Subsequence
vector<int> find_longest_increasing_subsequence(vector<int> &a)
{
	vector<int> p(a.size());
	vector<int> b;
	int u, v;

	if (a.empty()) return b;

	b.push_back(0);

	for (size_t i = 1; i < a.size(); i++) {
		// If next element a[i] is greater than last element of current longest subsequence a[b.back()], just push it at back of "b" and continue
		if (a[b.back()] < a[i]) {
			p[i] = b.back();
			b.push_back(i);
			continue;
		}

		// Binary search to find the smallest element referenced by b which is just bigger than a[i]
		// Note : Binary search is performed on b (and not a). Size of b is always <=k and hence contributes O(log k) to complexity.    
		for (u = 0, v = b.size() - 1; u < v;) {
			int c = (u + v) / 2;
			if (a[b[c]] < a[i]) u = c + 1; else v = c;
		}

		// Update b if new value is smaller then previously referenced value 
		if (a[i] < a[b[u]]) {
			if (u > 0) p[i] = b[u - 1];
			b[u] = i;
		}
	}

	for (u = b.size(), v = b.back(); u--; v = p[v]) b[u] = v;

	return b;
}

int main() {
	// your code goes here

	vector<int> vec = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };

	vector<int> longest_inc_subseq = find_longest_inc_subseq(vec);

	for_each(longest_inc_subseq.begin(), longest_inc_subseq.end(), [](int val) { cout << val << ' '; });

	return 0;
}