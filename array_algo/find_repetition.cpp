#include <iostream>
#include <vector>
#include <limits>
using namespace std;

/* Question:
Given a sorted array of integers, write a function that will return the number with the biggest
number of repetitions.
*/

int find_repetition(vector<int> &vec) {
	int curr_max = numeric_limits<int>::min();
	int prev = 0;
	int big_num_o_rep = 0;
	int count = 0;

	for (int i = 0; i < vec.size(); i++) {
		if (i > 0 && vec[i] == prev) {
			count++;
		}
		else {
			if (count > 0 && count > curr_max) {
				big_num_o_rep = prev;
				curr_max = count;
				count = 0;
			}
		}

		prev = vec[i];
	}

	return big_num_o_rep;
}

int main() {
	// your code goes here

	vector<int> vec = { 1, 2, 3, 3, 4, 5, 5, 5, 5, 8, 9, 12, 15, 15, 15, 19 };

	cout << find_repetition(vec) << endl;

	return 0;
}