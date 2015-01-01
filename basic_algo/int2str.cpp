#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

/*
Question: Please write an algorithm to convert an Integer (int) to a String (char*) / std::string
*/

char *int2str(int num) {
	bool is_negative = false;
	int index = 0;

	if (num < 0) {
		is_negative = true;
		num = num * (-1);
	}
	
	index = log10(num);

	if (is_negative) {
		index = index + 1;
	}

	char *str = new char[index + 1];
	memset(str, '\0', index + 1);

	while (num) {
		str[index] = '0' + (num % 10);
		index--;

		num = num / 10;
	}

	if (is_negative) {
		str[0] = '-';
	}

	return str;
}

string IntToString(int number) {
  bool isNegative = false;
  int index = 0;
  string str; // or string str(index + 1, '0');
  
  if (number < 0) {
    isNegative = true;
    number = abs(number);
    index = 1;
  }
  
  index += log10(number);
  str.resize(index+1);
  
  while (number) {
    str[index--] = '0' + (number % 10);
    number /= 10;
  }
  
  if (isNegative) {
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
