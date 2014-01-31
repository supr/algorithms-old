#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int roman_to_integer(const string &str);


bool is_valid_roman_string(const string &str, unordered_map<char, int> &ht) {
	if (str.size() < 1) {
		return false;
	}

	for (int i = 0; i < str.size() - 1; i++) {
		auto it = ht.find(str[i]);

		if (it == ht.end()) {
			return false;
		}
	}

	return true;
}

int roman_to_integer(const string &str) {
	int number = 0;
	unordered_map<char, int> roman;
	roman['M'] = 1000;
	roman['D'] = 500;
	roman['C'] = 100;
	roman['L'] = 50;
	roman['X'] = 10;
	roman['V'] = 5;
	roman['I'] = 1;

	if (!is_valid_roman_string(str, roman)) {
		return -1;
	}

	for (int i = 0; i < str.size() - 1; i++) {
		if (roman[str[i]] < roman[str[i + 1]]) {
			number -= roman[str[i]];
		}
		else {
			number += roman[str[i]];
		}
	}

	number += roman[str[str.size() - 1]];
	
	return number;
}

int main(int argc, char** argv)
{
	assert(1066, roman_to_integer("MLXVI"));
	assert(-1, roman_to_integer("ZMLXVI"));
	assert(6, roman_to_integer("VI"));
	assert(1, roman_to_integer("I"));
	assert(-1, roman_to_integer(""));
	assert(-1, roman_to_integer("123123"));
	assert(100, roman_to_integer("VIX"));
}