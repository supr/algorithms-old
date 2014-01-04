#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Question: Search in Rotated Sorted Array II

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?
Would this affect the run-time complexity? How and why?
Write a function to determine if a given target is in the array.

Average Case: O(log n)
Worst Case: e.g. search for 1: 3,1,3,3,3 -> O(n)
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
			return rotated_bin_search(vec, mid + 1, right, value);
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
	else {
		if (value < vec[mid] && vec[left] < vec[mid]) {
			return rotated_bin_search(vec, left, mid - 1, value);
		}
		else {
			return rotated_bin_search(vec, left + 1, right, value);
		}
	}
}

int main() {
	// your code goes here

	vector<int> vec = { 4, 5, 6, 7, 0, 1, 2 };

	for (int i = 0; i < vec.size(); i++) {
		cout << rotated_bin_search(vec, 0, vec.size() - 1, vec[i]) << ' ';
	}
	cout << "\n\n";

	vector<int> vec2 = { 1, 2, 3, 3, 3 };

	for (int i = 0; i < vec2.size(); i++) {
		for_each(vec2.begin(), vec2.end(), [](int value){ cout << value << ' '; });
		cout << "\n";
		cout << "number 1 found at index: " << rotated_bin_search(vec2, 0, vec2.size() - 1, 1) << endl;
		rotate(vec2.begin(), vec2.end() - 1, vec2.end());
	}

	cout << "\n\n";

	vector<int> vec3 = { 1, 3, 3, 3, 3 };

	for (int i = 0; i < vec3.size(); i++) {
		for_each(vec3.begin(), vec3.end(), [](int value){ cout << value << ' '; });
		cout << "\n";
		cout << "number 1 found at index: " << rotated_bin_search(vec3, 0, vec3.size() - 1, 1) << endl;
		rotate(vec3.begin(), vec3.end() - 1, vec3.end());
	}

	return 0;
}