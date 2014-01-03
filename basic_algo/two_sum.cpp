#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Question: Given an array of integers, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.
You may assume that each input would have exactly one solution.
Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

pair<int, int> two_sum(vector<int> &vec, int sum) {
	unordered_map<int, int> hs;

	for (int i = 0; i < vec.size(); i++) {
		hs.insert(make_pair(sum - vec[i], i));
	}

	for (int i = 0; i < vec.size(); i++) {
		auto it = hs.find(vec[i]);

		if (it != hs.end()) {
			return pair<int, int>(it->second, i);
		}
	}

	return pair<int, int>(-1, -1);
}

int main() {
	vector<int> vec = { 2, 7, 11, 15 };

	pair<int, int> p = two_sum(vec, 9);

	cout << "index 1: " << p.first << ", index 2: " << p.second << endl;
	return 0;
}
