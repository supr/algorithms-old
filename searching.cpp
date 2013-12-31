#include <iostream>
#include <vector>
using namespace std;

/*
Find the minimum element in a sorted and rotated array

A sorted array is rotated at some unknown point, find the minimum element in it.

Following solution assumes that all elements are distinct.

Examples

Input: {5, 6, 1, 2, 3, 4}
Output: 1

Input: {1, 2, 3, 4}
Output: 1

Input: {2, 1}
Output: 1
*/
int get_min_in_rotation(vector<int> &vec, int l, int r) {
	// base case
	if (vec[l] < vec[r]) return vec[l];

	int mid = l + (r - l) / 2;

	// check for rotation point
	if (vec[mid + 1] < vec[mid]) {
		return vec[mid + 1];
	}
	// if the most right element is larger than the middle element, the min is in left half
	else if (vec[r] > vec[mid]) {
		return get_min_in_rotation(vec, l, mid);
	}
	// if the most right element is smaller than the middle element, the min is in right half
	else if (vec[r] < vec[mid]) {
		return get_min_in_rotation(vec, mid + 1, r);
	}
	// if most right element equals the middle element
	// handles the following input with duplicates
	else {
		// handles the following input: 9,1,8,8,8
		if (vec[l] > vec[r]) {
			return get_min_in_rotation(vec, l, mid);
		}
		// handles the following input: 8,1,8,8,8
		// linear search
		return get_min_in_rotation(vec, l + 1, r);
	}
}

int main() {
	vector<int> vec = { 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2 };

	cout << get_min_in_rotation(vec, 0, vec.size() - 1) << endl;
}