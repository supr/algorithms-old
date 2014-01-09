#include <iostream>
#include <vector>
using namespace std;

/* Question: How to find the k smallest elements from an array.

Find the k smallest elements from the set of n numbers in O(n) time complexity

Solution: is based on Qickselect

Time Complexity:
Expected: O(n)
Worst Case: O(n^2)
*/

int rand_partition(vector<int> &vec, int low, int high) {
	int l = low;
	int r = high;
	int pivot_index = l + rand() % (r - l); // (low + high) / 2; 
	int pivot = vec[pivot_index];

	while (true) {
		while (vec[l] < pivot) l++;
		while (vec[r] > pivot) r--;
		if (l > r) break;
		std::swap(vec[l++], vec[r--]);
	}

	return l;
}

int rand_selection(vector<int> &vec, int l, int r, int k) {
	if (l == r) {
		return vec[l];
	}

	int pivot_index = rand_partition(vec, l, r);

	if (k == pivot_index) {
		return vec[pivot_index];
	}
	else if (k > pivot_index) {
		return rand_selection(vec, pivot_index + 1, r, k);
	}
	else if (k < pivot_index) {
		return rand_selection(vec, l, pivot_index - 1, k);
	}
}

int find_k_smallest_element(vector<int> &vec, int k) {
	return rand_selection(vec, 0, vec.size() - 1, k);
}

int main() {
	// your code goes here

	srand(time(0));

	vector<int> vec = { 10, 15, 2, 4, 1, 7, 5 };

	for (int i = 0; i < vec.size(); i++) {
		cout << find_k_smallest_element(vec, i) << endl;
	}

	return 0;