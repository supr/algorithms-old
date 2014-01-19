#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
You are given an array of integers (both positive and negative). Find the contiguous
sequence with the largest sum. Return the sum.

Example: Input: 2, 3, -8, -1, 2, 4, -2, 3
Contigous sequence with the largest sum: 2, 4, -2, 3
*/

vector<int> contig_seq_with_largest_sum(vector<int> &vec) {
	int start_index = 0;
	int start_index_tmp = 0;
	int end_index = 0;
	int current_sum = 0;
	int max_sum = 0;
	vector<int> seq_largest_sum;

	for (int i = 0; i < vec.size(); i++) {
		current_sum += vec[i];

		if (current_sum > max_sum) {
			max_sum = current_sum;
			start_index = start_index_tmp;
			end_index = i;
		}

		if (current_sum < 0) {
			current_sum = 0;
			start_index_tmp = i + 1;
		}
	}

	seq_largest_sum.insert(seq_largest_sum.begin(), vec.begin() + start_index, vec.begin() + end_index + 1);

	return seq_largest_sum;
}

int main() {
	// your code goes here

	vector<int> vec = { 2, 3, -8, -1, 2, 4, -2, 3 };

	vector<int> seq_largest_sum = contig_seq_with_largest_sum(vec);

	for_each(seq_largest_sum.begin(), seq_largest_sum.end(), [](int value) { cout << value << ' '; });

	return 0;
}