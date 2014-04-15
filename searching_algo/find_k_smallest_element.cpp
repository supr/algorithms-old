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

int rand_partition(vector<int> &vec, int left, int right) {
    int pivot_index = left + rand() % (right - left + 1);
    int pivot = vec[pivot_index];

    swap(vec[pivot_index], vec[right]);  // Move pivot to end
    int store_index = left;
    
    for(int i = left; i < right; i++) {
    	if(vec[i] <= pivot) {
            swap(vec[store_index], vec[i]);
            store_index++;
    	}
    }
    
    swap(vec[right], vec[store_index]);  // Move pivot to its final place
    return store_index;
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

	vector<int> vec = { 10, 15, 2, 4, 1, 7, 5, 1, 10 };

	for (int i = 0; i < vec.size(); i++) {
		cout << find_k_smallest_element(vec, i) << ' ';
	}

	return 0;
}
