#include <iostream>
#include <unordered_set>
using namespace std;

/*
Question: Remove Duplicate Characters in String

Remove duplicate characters in a given string keeping only the first occurrences. For example, if
the input is ‘tree traversal’ the output will be ‘tre avsl’.
*/

string remove_duplicates(string &str) {
	unordered_set<char> hs;
	string out;

	for (int i = 0; i < str.size(); i++) {
		auto it = hs.find(str[i]);

		if (it == hs.end()) {
			out.push_back(str[i]);
			hs.insert(str[i]);
		}
	}

	return out;
}

int main() {
	// your code goes here

	string s = "tree traversal";
	cout << remove_duplicates(s) << endl;

	return 0;
}