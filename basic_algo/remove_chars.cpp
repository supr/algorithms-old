#include <iostream>
#include <unordered_map>
#include <cassert>
using namespace std;

/* Question:
Write an efficient function that deletes characters from an ASCII
string. Use the prototype string removeChars( string str, string remove );
where any character existing in remove must be deleted from str. For example,
given a str of "Battle of the Vowels: Hawaii vs. Grozny" and a remove of
"aeiou", the function should transform str to “Bttl f th Vwls: Hw vs. Grzny”.
Justify any design decisions you make, and discuss the efficiency of your solution.
*/

string remove_chars(string str, string remove) {
	int total = 0;
	unordered_map<char, int> ht;

	for (int i = 0; i < remove.size(); i++) {
		auto it = ht.find(remove[i]);

		if (it == ht.end()) {
			ht.insert(make_pair(remove[i], 1));
		}
		else {
			it->second++;
		}
	}

	for (int i = 0; i < str.size(); i++) {
		auto it = ht.find(str[i]);

		if (it == ht.end() || it->second == 0) {
			str[total] = str[i];
			total++;
		}
	}

	str.resize(total);

	return str;
}

int main() {
	// your code goes here

	string s = "Battle of the Vowels: Hawaii vs. Grozny";
	string remove = "aeiou";
	assert(remove_chars(s, remove) == "Bttl f th Vwls: Hw vs. Grzny");

	return 0;
}