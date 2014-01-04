#include <iostream>
#include <vector>
using namespace std;

/*
Question: Search in Rotated Sorted Array

Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
*/

int rotated_bin_search(vector<int> &vec, int left, int right, int value) {
	if (left > right) {
		return -1;
	}

	int mid = left + (right - left) / 2;

	if (vec[mid] == value) {
		return mid;
	}
	else if (vec[right] > vec[mid]) {
		if (value >= vec[mid]) {
			return rotated_bin_search(vec, mid, right + 1, value);
		}
		else {
			return rotated_bin_search(vec, left, mid - 1, value);
		}
	}
	else if (vec[right] < vec[mid]) {
		if (value >= vec[left]) {
			return rotated_bin_search(vec, left, mid - 1, value);
		}
		else {
			return rotated_bin_search(vec, mid + 1, right, value);
		}
	}
}

int main() {
	// your code goes here

	vector<int> vec = { 4, 5, 6, 7, 0, 1, 2 };

	for (int i = 0; i < vec.size(); i++) {
		cout << rotated_bin_search(vec, 0, vec.size() - 1, vec[i]) << ' ';
	}

	return 0;
}