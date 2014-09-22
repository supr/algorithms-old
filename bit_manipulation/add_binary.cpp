#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
Question: Add binary

Given two binary strings, return their sum (also a binary string).
For example,
a = "11"
b = "1"
Return "100".
*/

string zeroPadding(string s, int bits) {
  for (int i = 0; i < bits; i++) {
    s = "0" + s;
  } 
  
  return s;
}

string add_binary(string in1, string in2) {
	string out;
	int diff = abs(in1.size() - in2.size());

	if (in1.size() > in2.size()) {
    in2 = zeroPadding(in2, diff);
	}
	else if (in2.size() > in1.size()) {
    in1 = zeroPadding(in1, diff);
	}

	char digit;
	char carry = '0';

	for (int i = in1.size() - 1; i >= 0; i--) {
		if (carry == '0') {
			if (in1[i] == '1' && in2[i] == '1') {
				carry = '1';
				digit = '0';
			}
			else if (in1[i] == '0' && in2[i] == '0') {
				carry = '0';
				digit = '0';
			}
			else {
				carry = '0';
				digit = '1';
			}
		}
		else {
			if (in1[i] == '1' && in2[i] == '1') {
				carry = '1';
				digit = '1';
			}
			else if (in1[i] == '0' && in2[i] == '0') {
				carry = '0';
				digit = '1';
			}
			else {
				carry = '1';
				digit = '0';
			}
		}

		out = digit + out;
	}

	if (carry == '1') {
		out = carry + out;
	}
	return out;
}

int main() {
	// your code goes here

	cout << add_binary("11", "1") << endl;

  cout << add_binary("1100", "111") << endl;

  cout << add_binary("1", "1") << endl;

	return 0;
}