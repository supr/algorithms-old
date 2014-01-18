#include <iostream>
using namespace std;

/* Question:
Compute the nth Fibonacci number.

Solution:
- recursive: O(2^n)
- iterative: O(n)

*/

int fibonacci_recursive(int n) {
	if (n <= 1) {
		return n;
	}

	return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_iterative(int n) {
	int zero = 0;
	int first = 1;
	int num = 0;

	if (n <= 1) {
		return n;
	}

	for (int i = 2; i <= n; i++) {
		num = zero + first;
		zero = first;
		first = num;
	}

	return num;
}

int main() {
	// your code goes here

	for (int i = 0; i < 20; i++) {
		cout << "recursive: " << fibonacci(i) << ", iterative: " << fibonacci_iterative(i) << endl;
	}

	return 0;
}