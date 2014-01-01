#include <iostream>
using namespace std;

/*
Question: Please write an algorithm to convert a String (char*) into an Integer (int)
*/

int str2int(char *str) {
	int number = 0;

	if (str == NULL) {
		return -1;
	}

	while (*str != '\0') {
		int digit = static_cast<int>(*str) - static_cast<int>('0');
		number = digit + number * 10;
		str++;
	}

	return number;
}

int main() {
	char *str = "12345";
	cout << str2int(str) << endl;

	char *str2 = "44552233";
	cout << str2int(str2) << endl;

	return 0;
}