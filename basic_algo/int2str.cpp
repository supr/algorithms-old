#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

/*
Question: Please write an algorithm to convert an Integer (int) to a String (char*)
*/

char *int2str(int num) {
	bool is_negative = false;
	int str_len_index = 0;

	if (num < 0) {
		is_negative = true;
		num = num * (-1);
	}

	if (is_negative) {
		str_len_index = log10(num) + 2;
	}
	else {
		str_len_index = log10(num) + 1;
	}

	char *str = new char[str_len_index];
	memset(str, '\0', str_len_index);

	while (num) {
		int remainer = num % 10;

		str[str_len_index - 1] = '0' + remainer;
		str_len_index--;

		num = num / 10;
	}

	if (is_negative) {
		str[0] = '-';
	}

	return str;
}

int main() {
	char *str = int2str(12345);
	cout << str << endl;

	char *str2 = int2str(44552233);
	cout << str2 << endl;

	char *str3 = int2str(-120);
	cout << str3 << endl;

	delete str;
	delete str2;
	delete str3;

	return 0;
}