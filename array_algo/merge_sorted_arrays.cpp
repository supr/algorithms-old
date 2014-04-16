#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* Question:
Merge 2 sorted arrays into arr1
arr1: 3 4 7 8 10
arr2: 1 2 9 10

after merging: 1 2 3 4 7 8 9 10
*/

void merge_sorted_arrays(vector<int> &arr1, const vector<int> &arr2) {
	int i = arr1.size() - 1;
	int j = arr2.size() - 1;
	int total_index = arr1.size() + arr2.size();
	int dublicates = 0;

	arr1.resize(total_index);
	total_index--;

	while (i >= 0 && j >= 0) {
		if (arr1[i] > arr2[j]) {
			arr1[total_index] = arr1[i];
			i--;
		}
		else if (arr1[i] < arr2[j]) {
			arr1[total_index] = arr2[j];
			j--;
		}
		else {
			arr1[total_index] = arr1[i];
			i--;
			j--;
			dublicates++;
		}

		total_index--;
	}

	while (i >= 0) {
		arr1[total_index] = arr1[i];
		i--;
		total_index--;
	}

	while (j >= 0) {
		arr1[total_index] = arr2[j];
		j--;
		total_index--;
	}

	arr1.erase(arr1.begin(), arr1.begin() + dublicates);
}

int main() {
	vector<int> arr1 = { 3, 4, 7, 8, 10 };
	vector<int> arr2 = { 1, 2, 9, 10 };

	merge_sorted_arrays(arr1, arr2);

	for_each(arr1.begin(), arr1.end(), [](int value) { cout << value << ' '; });

	return 0;
}
