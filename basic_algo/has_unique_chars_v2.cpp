#include <iostream>
#include <string>
#include <bitset>
using namespace std;

/* Question:
Implement an algorithm to determine if a string has all unique characters. What if
you cannot use additional data structures.

Solution:
- Implemente in c++, uses bitsets -> 8 chars are stored in 4 byte
*/

bool hash_unique_chars(const string &str) {
	bitset<256> bs = { 0 };

	for (int i = 0; i < str.size(); i++) {
		if (bs.test(str[i] - 'A')) {
			return false;
		}
		else {
			bs.set(str[i] - 'A');
		}
	}

	return true;
}

int main() {
	// your code goes here

	string str1 = "Hello";
	string str2 = "Hansi";

	bool result1 = hash_unique_chars(str1);
	if (result1) {
		cout << "The string \"" << str1 << "\" has unique characters" << endl;
	}
	else {
		cout << "The string \"" << str1 << "\" does not have unique characters" << endl;
	}

	bool result2 = hash_unique_chars(str2);
	if (result2) {
		cout << "The string \"" << str2 << "\" has unique characters" << endl;
	}
	else {
		cout << "The string \"" << str2 << "\" does not have unique characters" << endl;
	}

	return 0;
}