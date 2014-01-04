#include <iostream>
#include <vector>
using namespace std;

/*
Given an unsorted integer array, find the first missing positive integer.
For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.
*/

int find_missing_positive_int(vector<int> &vec) {
	int n = vec.size();
	int total_sum = n * (n + 1) / 2;
	int sum = 0;

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > 0) {
			sum += vec[i];
		}
	}

	return total_sum - sum;
}

int main() {
	vector<int> vec = { 1, 2, 0 };
	cout << find_missing_positive_int(vec) << endl;

	vector<int> vec2 = { 3, 4, -1, 1 };
	cout << find_missing_pos_int(vec2) << endl;

	return 0;
}
