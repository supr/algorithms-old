#include <iostream>
using namespace std;

/* Question:
Write a method to count the number of 2s between 0 and n.
*/

int count_2s(int number) {
	int count = 0;

	while (number) {
		if ((number % 10) == 2) {
			count++;
		}

		number /= 10;
	}

	return count;
}

int main() {
	// your code goes here

	cout << count_2s(12322) << endl;

	return 0;
}