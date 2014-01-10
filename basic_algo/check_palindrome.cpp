#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/* Question:
Please implement a function which checks whether a number is a palindrome or not. For example,
121 is a palindrome, while 123 is not.

Solution:
- convert integer to string and compared the reversed string with the original string
- generate the reversed integer number and compare it with the original number
*/

bool is_palindrome1(int number) {
	stringstream ss;
	ss << number;
	string s = ss.str();
	int j = s.size() - 1;

	for (int i = 0; i < s.size() / 2; i++) {
		if (s[i] != s[j--]) {
			return false;
		}
	}

	return true;
}

bool is_palindrome2(int number) {
	int number_copy = number;
	int reversed = 0;

	while (number) {
		reversed = reversed * 10 + number % 10;
		number /= 10;
	}

	if (reversed == number_copy) {
		return true;
	}
	return false;
}

int main() {
	// your code goes here

	bool result1 = is_palindrome1(121);
	if (result1) {
		cout << "The number 121 is a Palindome" << endl;
	}
	else {
		cout << "The number 121 is not a Palindome" << endl;
	}

	bool result2 = is_palindrome1(123);
	if (result2) {
		cout << "The number 123 is a Palindome" << endl;
	}
	else {
		cout << "The number 123 is not a Palindome" << endl;
	}

	bool result3 = is_palindrome2(212);
	if (result3) {
		cout << "The number 212 is a Palindome" << endl;
	}
	else {
		cout << "The number 212 is not a Palindome" << endl;
	}

	bool result4 = is_palindrome2(223);
	if (result4) {
		cout << "The number 223 is a Palindome" << endl;
	}
	else {
		cout << "The number 223 is not a Palindome" << endl;
	}

	return 0;
}