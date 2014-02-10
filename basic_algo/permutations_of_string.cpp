#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
Write a method to compute all permutations of a string
*/

void permutations_of_string(string s, vector<string> &vec, int i) {
	if (i == s.size()) {
		vec.push_back(s);
	}
	else
	{
		for (int j = i; j < s.size(); j++)
		{
			swap(s[i], s[j]);
			permutations_of_string(s, vec, i + 1);
			swap(s[i], s[j]);
		}
	}
}
int main() {
	vector<string> permutations;
	permutations_of_string("abc", permutations, 0);

	for_each(permutations.begin(), permutations.end(), [](string val) { cout << val << ' '; });

	return 0;
}