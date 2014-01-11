#include <iostream>
#include <string>
using namespace std;

/* Question:
Find the longest palindrome in a input string.

Example - aaabbaaaccdeqjncsdddmmmkkkmmmddd

Answer - dddmmmkkkmmmddd
*/

// searches for the largest palindrome for a given middle point left, right
// compares each character on the left with the character on the right side
void palindrome_search(const string &s, int left, int right, string &longest_palindrome) {
	bool found = false;

	while (left >= 0 && right < s.size()) {
		if (s[left] == s[right]) {
			left--;
			right++;
			found = true;
		}
		else {
			break;
		}

	}

	if (found) {
		left++;
		right--;

		if (right - left + 1 > longest_palindrome.size()) {
			longest_palindrome = s.substr(left, right - left + 1);
		}
	}
}

string find_longest_palindrome(const string &s) {
	string longest_palindrome;

	for (int i = 0; i < s.size(); i++) {
		// pair elements in the middle of the palindrome
		if (i < s.size() - 2 && s[i] == s[i + 1]) {
			palindrome_search(s, i - 1, i + 2, longest_palindrome);
		}

		// single element in the middle of the palindrome
		if (i < s.size() - 1) {
			palindrome_search(s, i - 1, i + 1, longest_palindrome);
		}
	}

	return longest_palindrome;
}

int main() {
	// your code goes here

	cout << find_longest_palindrome("aaabbaaaccdeqjncsdddmmmkkkmmmddd") << endl;

	return 0;
}