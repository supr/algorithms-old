#include <vector>
#include <queue>
#include <iostream>
using namespace std;

/*
Question: Question: Please find the smallest k numbers (in value) out of n numbers. For example, if given an array with eight numbers
{4, 5, 1, 6, 2, 7, 3, 8, please return the least four numbers 1,2,3, and 4.
*/

priority_queue<int, vector<int>, std::less<int>> find_k_min_numbers(vector<int> &vec, int k) {
	priority_queue<int, vector<int>, std::less<int>> pq;

	for (int i = 0; i < vec.size(); i++) {
		if (pq.size() < k) {
			pq.push(vec[i]);
		}
		else {
			if (pq.top() > vec[i]) {
				pq.pop();
				pq.push(vec[i]);
			}
		}
	}

	return pq;
}

int main() {
	vector<int> vec = { 4, 5, 1, 6, 2, 7, 3, 8 };

	priority_queue<int, vector<int>, std::less<int>> pq = find_k_min_numbers(vec, 4);

	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}

	return 0;
}