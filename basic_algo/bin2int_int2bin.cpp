#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
Question: Int to Bin, Bin to Int

Implement an algoritm to convert an integer number into a binary string
Implement an algorithm to convert an binary string into an integer number
*/

string int2bin(int n) {
	int bin_str_len = log2(n) + 1;
	char *bin_str = new char[bin_str_len];
	bin_str_len -= 1;

	while (n) {
		bin_str[bin_str_len] = '0' + n % 2;
		bin_str_len--;

		n = n >> 1;
	}

	string bin_str_out(bin_str);
	delete bin_str;

	return bin_str_out;
}

int bin2int(string bin_str) {
	int digit = 0;
	int value = 0;

	for (int i = bin_str.size() - 1; i >= 0; i--) {
		if (bin_str[i] == '1') {
			value += pow(2, digit);
		}

		digit++;
	}

	return value;
}

int main() {
	// your code goes here

	cout << int2bin(10) << endl;

	cout << bin2int("1010") << endl;

	return 0;
}