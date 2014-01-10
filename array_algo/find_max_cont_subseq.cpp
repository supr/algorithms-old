#include <iostream>
#include <vector>
using namespace std;

/* Question:
Find the sum of contiguous subarray within a one-dimensional array of numbers which has the
largest sum.
e.g. -2, -3, 4, -1, -2, 1, 5, -3
output: 4, -1, -2, 1, 5
*/

pair<int, int> find_max_cont_subseq(vector<int> &vec) {
	int start_tmp = 0;
	int start = 0;
	int end = 0;
	int max = 0;
	int current_sum = 0;

	for (int i = 0; i < vec.size(); i++) {
		current_sum += vec[i];

		if (current_sum > max) {
			end = i;
			start = start_tmp;
			max = current_sum;
		}

		if (current_sum < 0) {
			current_sum = 0;
			start_tmp = i + 1;
		}
	}

	return pair<int, int>(start, end);
}

int main() {
	// your code goes here

	vector<int> vec = { -2, -3, 4, -1, -2, 1, 5, -3 };
	pair<int, int> p = find_max_cont_subseq(vec);

	for (int i = p.first; i <= p.second; i++) {
		cout << vec[i] << ' ';
	}

	return 0;
}