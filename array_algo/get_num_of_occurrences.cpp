#include <vector>
#include <queue>
#include <iostream>
using namespace std;

/*
Question: Please implement a function to find how many times a number occurs in a sorted array.
For instance, the output is 4 when the inputs are an array {1, 2, 3, 3, 3, 3, 4, 5} and the number 3 because 3
occurs 4 times in the given array.

The algorithm is implemented in two versions:
- int get_num_of_occurrences1(vector<int> &vec, int num)
  Time Complexity: O(n) ... worst case
- int get_num_of_occurrences2(vector<int> &vec, int num)
  Time Complexity: O(log(n)) ... worst case
*/

int binary_search(vector<int> &vec, int l, int r, int val) {
	if (l > r) {
		return -1;
	}

	int mid = l + (r - l) / 2;

	if (vec[mid] == val) {
		return mid;
	}
	else if (vec[mid] < val) {
		return binary_search(vec, mid + 1, r, val);
	}
	else if (vec[mid] > val) {
		return binary_search(vec, l, mid - 1, val);
	}
}

int get_start_index(vector<int> &vec, int num, int first_found_index) {
	while (first_found_index > 0) {
		first_found_index--;

		if (vec[first_found_index] != num) {
			first_found_index++;
			break;
		}
	}

	return first_found_index;
}

int get_end_index(vector<int> &vec, int num, int first_found_index) {
	while (first_found_index < vec.size() - 1) {
		first_found_index++;

		if (vec[first_found_index] != num) {
			first_found_index--;
			break;
		}
	}

	return first_found_index;
}

int get_num_of_occurrences1(vector<int> &vec, int num) {
	int index = binary_search(vec, 0, vec.size() - 1, num);

	if (index != -1) {
		return get_end_index(vec, num, index) - get_start_index(vec, num, index);
	}

	return index;
}

int get_first_occurrence(vector<int> &vec, int l, int r, int val) {
	if (l > r) {
		return -1;
	}

	int mid = l + (r - l) / 2;

	if (vec[mid] == val) {
		if (mid > 0 && vec[mid - 1] == val) {
			return get_first_occurrence(vec, l, mid - 1, val);
		}
		else {
			return mid;
		}
	}
	else if (vec[mid] < val) {
		return get_first_occurrence(vec, mid + 1, r, val);
	}
	else if (vec[mid] > val) {
		return get_first_occurrence(vec, l, mid - 1, val);
	}
}

int get_last_occurrence(vector<int> &vec, int l, int r, int val) {
	if (l > r) {
		return -1;
	}

	int mid = l + (r - l) / 2;

	if (vec[mid] == val) {
		if (mid < vec.size() - 1 && vec[mid + 1] == val) {
			return get_last_occurrence(vec, mid + 1, r, val);
		}
		else {
			return mid;
		}
	}
	else if (vec[mid] < val) {
		return get_last_occurrence(vec, mid + 1, r, val);
	}
	else if (vec[mid] > val) {
		return get_last_occurrence(vec, l, mid - 1, val);
	}
}

int get_num_of_occurrences2(vector<int> &vec, int num) {
	int first_index = get_first_occurrence(vec, 0, vec.size() - 1, num);
	int last_index = get_last_occurrence(vec, 0, vec.size() - 1, num);

	if (first_index != -1 && last_index != -1) {
		return last_index - first_index;
	}

	return -1;
}

int main() {
	vector<int> vec = { 1, 2, 3, 3, 3, 3, 4, 5 };

	cout << get_num_of_occurrences1(vec, 3) << endl;
	cout << get_num_of_occurrences2(vec, 3) << endl;

	return 0;
}