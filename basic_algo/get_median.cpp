#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <ctime> 
using namespace std;

/*
Question: Find median of an unsorted array.

Solution: is based on Qickselect

Time Complexity:
Expected: O(n)
Worst Case: O(n^2)

Possible Improvement:
- median of medians -> Worst Case: O(n)
*/

int rand_partition(vector<int> &a, int left, int right) {
	int pivotIndex = left + (rand() % (right - left));
	//int m = left + (right - left) / 2; //... to test the algo...no rand at this point 
	int pivot = a[pivotIndex];
	int i = left;
	int j = right;

	do {
		while (a[i] < pivot) i++; // find left element > pivot 
		while (a[j] > pivot) j--; // find right element < pivot 

		// if i and j not already overlapped, we can swap 
		if (i < j) {
			swap(a[i], a[j]);
		}
	} while (i < j);

	return i;
}

// Returns the n-th smallest element of list within left..right inclusive (i.e. n is zero-based). 
int rand_select(vector<int> &a, int left, int right, int n) {
	if (left == right) {        // If the list contains only one element 
		return a[left];  // Return that element 
	}

	int pivotIndex = rand_partition(a, left, right);

	// The pivot is in its final sorted position 
	if (n == pivotIndex) {
		return a[n];
	}
	else if (n < pivotIndex) {
		return rand_select(a, left, pivotIndex - 1, n);
	}
	else {
		return rand_select(a, pivotIndex + 1, right, n);
	}
}

int get_median(vector<int> vec) {
	int n = vec.size() / 2;
	return rand_select(vec, 0, vec.size() - 1, n);
}

int get_median2(vector<int> vec) {
	int n = vec.size() / 2;

	nth_element(vec.begin(), vec.begin() + n, vec.end());
	return vec.at(n);
}

int main() {
	// your code goes here 

	srand(time(0));

	vector<int> numbers = { 9, 2, 4, 3, 8, 5, 7, 6, 1 };
	cout << get_median(numbers) << endl;
	cout << get_median2(numbers) << '\n' << endl;

	vector<int> numbers2 = { 6, 8, 2 };
	cout << get_median(numbers2) << endl;
	cout << get_median2(numbers2) << '\n' << endl;

	vector<int> numbers3 = { 1, 10, 5, 7 };
	cout << get_median(numbers3) << endl;
	cout << get_median2(numbers3) << '\n' << endl;

	vector<int> numbers4 = { 11, 3, 7, 8 };
	cout << get_median(numbers4) << endl;
	cout << get_median2(numbers4) << '\n' << endl;

	vector<int> numbers5 = { 3, 1 };
	cout << get_median(numbers5) << endl;
	cout << get_median2(numbers5) << endl;

	return 0;
}