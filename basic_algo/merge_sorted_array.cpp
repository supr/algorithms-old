#include <iostream>
#include <algorithm>
using namespace std;

/*
Question: Note:
You may assume that A has enough space to hold additional elements from B. The number of
elements initialized in A and B are m and n respectively.

Note:
You may assume that A has enough space to hold additional elements from B. The number of
elements initialized in A and B are m and n respectively.
*/

void merge_sorted_array(vector<int> &vec1, vector<int> &vec2, int m, int n) {
	int index_vec1 = m - 1;
	int index_vec2 = n - 1;
	int total_index = vec1.size() - 1;

	while (index_vec1 >= 0 && index_vec2 >= 0) {
		if (vec1[index_vec1] > vec2[index_vec2]) {
			vec1[total_index] = vec1[index_vec1];
			index_vec1--;
		}
		else if (vec2[index_vec2] > vec1[index_vec1]) {
			vec1[total_index] = vec2[index_vec2];
			index_vec2--;
		}
		else if (vec1[index_vec1] == vec2[index_vec2]) {
			vec1[total_index] = vec2[index_vec2];
			index_vec1--;
			index_vec2--;
		}

		total_index--;
	}

	while (index_vec1 >= 0) {
		vec1[total_index] = vec1[index_vec1];
		index_vec1--;
		total_index--;
	}

	while (index_vec2 >= 0) {
		vec1[total_index] = vec2[index_vec2];
		index_vec2--;
		total_index--;
	}
}

int main() {
	vector<int> vec1 = { 1, 3, 7, 10, 15 };
	vector<int> vec2 = { 2, 4, 8, 11, 16, 19 };
	int m = vec1.size();
	int n = vec2.size();

	vec1.resize(vec1.size() + vec2.size());
	merge_sorted_array(vec1, vec2, m, n);

	for_each(vec1.begin(), vec1.end(), [](int value) { cout << value << ' '; });

	return 0;
}