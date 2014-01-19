#include <iostream>
#include <cmath>
using namespace std;

/* Question:
Implement a method rand7() given rand5(). That is, given a method that generates
a random number between 0 and 4 (inclusive), write a method that generates a
random number between 0 and 6 (inclusive).
*/

int rand5() {
	return rand() % 5;
}

int rand_0_1() {
	int num = 0;

	do {
		num = rand5();
	} while (num >= 2);

	return num;
}

int rand7_v1() {
	int num = 0;
	int digit = 0;

	do {
		num = 0;
		digit = 0;

		for (int i = 0; i < 3; i++) {
			int num_0_1 = rand_0_1();
			num += num_0_1 * pow(2, digit);
			digit++;
		}
	} while (num > 6);

	return num;
}

int rand7_v2() {
	while (true) {
		int number = rand5() + rand5() * 5;

		if (number < 21) {
			return number % 7;
		}
	}
}

int main() {
	// your code goes here

	srand(time(0));

	for (int i = 0; i < 10; i++) {
		cout << rand7_v1() << ' ';
	}

	cout << '\n';

	for (int i = 0; i < 10; i++) {
		cout << rand7_v2() << ' ';
	}

	return 0;
}