#include <iostream>
#include <string>
using namespace std;

/* Question:
Assume you have a method isSubstring which checks if one word is a
substring of another. Given two strings, s1 and s2, write code to check if s2 is
a rotation of s1 using only one call to isSubstring (e.g.,"waterbottle"is a rotation
of "erbottlewat").
*/

bool is_rotation1(const string &s1, const string &s2) {
	string identifier;
	identifier = s1[s1.size() - 1];
	identifier += s1[0];

	if (s1.size() != s2.size()) {
		return false;
	}

	int pos = s2.find(identifier);

	if (pos != string::npos) {
		string left_part = s2.substr(pos + 1, s2.size() - (pos + 1));
		string right_part = s2.substr(0, pos + 1);

		if (s1 == (left_part + right_part)) {
			return true;
		}
	}

	return false;
}

bool is_rotation2(const string &s1, const string &s2) {
	string s1s1 = s1 + s1;

	if (s1.size() != s2.size()) {
		return false;
	}

	int pos = s1s1.find(s2);

	if (pos != string::npos) {
		return true;
	}

	return false;
}

int main() {
	// your code goes here

	string s1 = "waterbottle";
	string s2 = "erbottlewa";
	bool result1 = is_rotation1("waterbottle", "erbottlewat");
	if (result1) {
		cout << "The string \"" << s2 << "\" is a rotation of the string \"" << s1 << endl;
	}
	else {
		cout << "The string \"" << s2 << "\" is not a rotation of the string \"" << s1 << endl;
	}

	bool result2 = is_rotation2("waterbottle", "erbottlewat");
	if (result2) {
		cout << "The string \"" << s2 << "\" is a rotation of the string \"" << s1 << endl;
	}
	else {
		cout << "The string \"" << s2 << "\" is not a rotation of the string \"" << s1 << endl;
	}

	return 0;
}