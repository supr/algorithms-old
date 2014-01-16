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

	// either the left or right half must be normally ordered
	// figure out which side is normally ordered
	// use the normally ordered side and figure out which half to search for value

	// if the right half is sorted
	else if (vec[mid] < vec[right]) {
		// if key is in the right half
		if (value > vec[mid] && value <= vec[right]) {
			return rotated_bin_search(vec, mid + 1, right, value);
		}
		// if key is in the left half
		else {
			return rotated_bin_search(vec, left, mid - 1, value);
		}
	}
	// if the left half is sorted
	else if (vec[mid] > vec[right]) {
		// if key is in the left half
		if (value >= vec[left] && value < vec[mid]) {
			return rotated_bin_search(vec, left, mid - 1, value);
		}
		// if key is in the right half
		else {
			return rotated_bin_search(vec, mid + 1, right, value);
		}
	}
	// if most right element equals the middle element
	// handles the following input with duplicates
	else if (vec[mid] == vec[right]) { // Right half is all repeats

		// handles the following input: 9,1,8,8,8
		if (vec[mid] != vec[left]) { // If left is diff., search it
			return rotated_bin_search(vec, left, mid - 1, value); // search left
		}
		else { // Else, we have to search both halves
			// handles the following input: 8,1,8,8,8
			int result = rotated_bin_search(vec, left, mid - 1, value); // Search left

			if (result == -1) {
				// handles the following input: 8,8,8,1,8
				return rotated_bin_search(vec, mid + 1, right, value); // Search right
			}

			return result;
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

	cout << "\n\n";

	vector<int> vec4 = { 15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14 };

	for (int i = 0; i < vec4.size(); i++) {
		for_each(vec4.begin(), vec4.end(), [](int value){ cout << value << ' '; });
		cout << "\n";
		cout << "number 15 found at index: " << rotated_bin_search(vec4, 0, vec4.size() - 1, 15) << endl;
		rotate(vec4.begin(), vec4.end() - 1, vec4.end());
	}

	vector<int> vec5 = { 9, 1, 3, 3, 3 };

	for (int i = 0; i < vec5.size(); i++) {
		for_each(vec5.begin(), vec5.end(), [](int value){ cout << value << ' '; });
		cout << "\n";
		cout << "number 9 found at index: " << rotated_bin_search(vec5, 0, vec5.size() - 1, 9) << endl;
		rotate(vec5.begin(), vec5.end() - 1, vec5.end());
	}

	cout << "\n\n";

	vector<int> vec6 = { 1, 8, 8, 8, 8 };

	for (int i = 0; i < vec6.size(); i++) {
		for_each(vec6.begin(), vec6.end(), [](int value){ cout << value << ' '; });
		cout << "\n";
		cout << "number 1 found at index: " << rotated_bin_search(vec6, 0, vec6.size() - 1, 1) << endl;
		rotate(vec6.begin(), vec6.end() - 1, vec6.end());
	}

	cout << "\n\n";

	return 0;
}