#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/*
Question: Anagram Strings
Given two strings, check if they are anagrams or not. Two strings are anagrams if they are written using the same 
exact letters, ignoring space, punctuation and capitalization. Each letter should have the same count in both 
strings. For example, "Eleven plus two" and "Twelve plus one" are meaningful anagrams of each other.
*/

bool are_anagram_strings1(string s1, string s2) {
	if (s1.size() != s2.size()) {
		return false;
	}

	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] != s2[i]) {
			return false;
		}
	}

	return true;
}

bool are_anagram_strings2(string s1, string s2) {
	if (s1.size() != s2.size()) {
		return false;
	}

	unordered_map<char, int> ht;

	for (int i = 0; i < s1.size(); i++) {
		auto it = ht.find(tolower(s1[i]));

		if (it == ht.end()) {
			ht.insert(make_pair(tolower(s1[i]), 1));
		}
		else {
			it->second++;
		}
	}

	for (int i = 0; i < s2.size(); i++) {
		auto it = ht.find(tolower(s2[i]));

		if (it == ht.end()) {
			return false;
		}
		else if (it == ht.end()) {
			if (it->second > 0) {
				it->second--;
			}
			else {
				return false;
			}
		}
	}

	return true;
}

int main() {

	cout << are_anagram_strings1("Eleven plus two", "Twelve plus one") << endl;
	cout << are_anagram_strings2("Eleven plus two", "Twelve plus one") << endl;

	return 0;
}
