#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/* Question:
Encode a String
aaaabbccdd -> a4b2c2d2
In minimun space and time complexity
*/

void encode_string(string &s) {
	int char_counter = 1;
	char prev = 0;
	int total_index = 0;

	for (int i = 0; i <= s.size(); i++) {
		// if current character is previous character -> increment char_count
		if (i > 0 && s[i] == prev) {
			char_counter++;
		}
		else if (i > 0 && s[i] != prev) {
			s[total_index++] = prev;

			// only encode if character repeats at least 2 times
			if (char_counter >= 2) {
				stringstream ss;
				ss << char_counter;

				for (int j = 0; j < ss.str().size(); j++) {
					s[total_index++] = ss.str()[j];
				}
			}

			char_counter = 1;
		}

		prev = s[i];
	}

	s = s.substr(0, total_index);
}

int main() {
	// your code goes here

	string s = "aaaabbccdd";

	encode_string(s);

	cout << s << endl;

	return 0;
}