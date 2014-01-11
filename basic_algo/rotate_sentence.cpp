#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// methode wiht 2 parameter, 1 param: sentence, 2 param: rotate sentece by x
// Example: "This is a sentence", 2 -> "a sentence This is"

string rotate_sentence(string s, int num_rotation) {
	int words_len = 0;
	int count_space = 0;

	for (int i = s.size() - 1; i >= 0; i--) {
		if (s[i] == ' ') {
			count_space++;

			if (count_space == num_rotation) {
				words_len = s.size() - words_len;
				break;
			}
		}

		words_len++;
	}

	rotate(s.begin(), s.begin() + words_len, s.end());

	s.insert(s.size() - words_len, " ");

	return s;
}

int main() {
	// your code goes here

	string s = "This is a sentence";
	cout << rotate_sentence(s, 2) << endl;

	return 0;
}