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
		for (int j = i; j < s.size(); j++) {
 			swap(s[i], s[j]);
			permutations_of_string(s, vec, i + 1);
			swap(s[i], s[j]);
		}
	}
}

vector<string> insert_at_all_positions(char ch, string s) {
	vector<string> result;

	for (int i = 0; i <= s.size(); i++) {
		string inserted = s.substr(0, i) + ch + s.substr(i);
		result.push_back(inserted);
	}

	return result;
}

vector<string> permutation_of_string2(string s) {
	vector<string> result;

	if (s.size() == 1) { // base case
		// return a vector<string> containing just s
		result.push_back(s);
		return result;
	}
	else {
		// separate the first character from the rest
		char first = s[0];
		string rest = s.substr(1);
		// get all permutationsOf the rest of the characters
		vector<string> simpler = permutation_of_string2(rest);  // recursive step
		
		// for each permutation
		for (string permutation : simpler) { // extra work // add the first character in all possible positions, and
			vector<string> additions = insert_at_all_positions(first, permutation); // put each result into a vector<string>

			for (string a : additions) {
				result.push_back(a);
			}
		}

		return result;
	}
}

int main() {
	vector<string> permutations;
	permutations_of_string("abc", permutations, 0);

	for_each(permutations.begin(), permutations.end(), [](string val) { cout << val << ' '; });

	return 0;
}