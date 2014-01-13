#include <iostream>
using namespace std;

/* Question:
Implement a function swap without a temporary variable.
*/

void my_swap(int &a, int &b) {
	a += b; // a = a + b
	b = a - b; // b = a + b - b
	a = a - b; // a = a + b - a
}

int main() {
	// your code goes here

	int a = 1;
	int b = 2;

	my_swap(a, b);

	cout << "a:" << a << "b: " << b << endl;

	return 0;
}