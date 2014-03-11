#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/*
Question: Int to Bin, Bin to Int

Implement an algoritm to convert an integer number into a binary string
Implement an algorithm to convert an binary string into an integer number
*/

string int2bin(unsigned int number) {
	string bin_str;
	unsigned int index = log2(number);
	bin_str.resize(index + 1);
	
	while(number) {
		bin_str[index--] = '0' + number % 2;
		number = number >> 1;
	}
	
	return bin_str;
}

unsigned int bin2int(string bin_str) {
	unsigned int digit = 0;
	unsigned int value = 0;

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
