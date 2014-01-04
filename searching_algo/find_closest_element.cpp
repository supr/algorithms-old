#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Question: Find the closest element of a given value in a sorted array.
*/

int rotated_bin_search(vector<int> &vec, int left, int right, int value) {
	if (left > right) {
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
		return rotated_bin_search(vec, mid + 1, right, value);
	}
	else if (value < vec[mid]) {
		return rotated_bin_search(vec, left, mid - 1, value);
	}
}

int main() {
	// your code goes here

	vector<int> vec = { 1, 3, 6, 10 };

	for (int i = 0; i <= *max_element(vec.begin(), vec.end()); i++) {
		cout << "value: " << i << ", index: " << rotated_bin_search(vec, 0, vec.size() - 1, i) << endl;
	}
	cout << "\n\n";

	return 0;
}