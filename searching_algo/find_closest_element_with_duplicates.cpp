#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Question: Find the closest element of a given value in a sorted array.
*/

int bin_search(vector<int> &vec, int left, int right, int value) {
	if (abs(right - left) == 1) {
		if (abs(vec[left] - value) < abs(vec[right] - value)) {
			return left;
		}
		else {
			return right;
		}
	}

	int mid = left + (right - left) / 2;

	if (vec[mid] == value) {
		return mid;
	}
	else if (value > vec[mid]) {
		return bin_search(vec, mid, right, value);
	}
	else if (value < vec[mid]) {
		return bin_search(vec, left, mid, value);
	}
}

int rotated_bin_search(vector<int> &vec, int left, int right, int value) {
	if (abs(right - left) == 1) {
		if (abs(vec[left] - value) < abs(vec[right] - value)) {
			return left;
		}
		else {
			return right;
		}
	}

	int mid = left + (right - left) / 2;

	if (vec[mid] == value) {
		return mid;
	}
	else if (vec[right] > vec[mid]) {
		if (value >= vec[mid]) {
			return rotated_bin_search(vec, mid, right, value);
		}
		else {
			return rotated_bin_search(vec, left, mid, value);
		}
	}
	else if (vec[right] < vec[mid]) {
		if (value >= vec[left]) {
			return rotated_bin_search(vec, left, mid, value);
		}
		else {
			return rotated_bin_search(vec, mid, right, value);
		}
	}
	else {
		if (value < vec[mid] && vec[left] < vec[mid]) {
			return rotated_bin_search(vec, left, mid, value);
		}
		else {
			// O(n)
			return rotated_bin_search(vec, left + 1, right, value);
		}
	}
}

int main() {
	// your code goes here

	vector<int> vec = { 1, 3, 6, 10, 16, 17 };
	vector<int> vec2 = { 1, 3, 3, 3 };

	for (int i = 0; i <= *max_element(vec.begin(), vec.end()); i++) {
		cout << "value: " << i << ", index: " << bin_search(vec, 0, vec.size() - 1, i) << ", " << rotated_bin_search(vec, 0, vec.size() - 1, i) << endl;
	}

	cout << "\n\n";

	for (int i = 0; i < vec.size(); i++) {
		cout << "value: " << "1" << ", index: " << rotated_bin_search(vec, 0, vec.size() - 1, 1) << endl;
		rotate(vec.begin(), vec.end() - 1, vec.end());
	}

	cout << "\n\n";

	for (int i = 0; i < vec2.size(); i++) {
		cout << "value: " << "1" << ", index: " << rotated_bin_search(vec2, 0, vec2.size() - 1, 1) << endl;
		rotate(vec2.begin(), vec2.end() - 1, vec2.end());
	}

	return 0;
}