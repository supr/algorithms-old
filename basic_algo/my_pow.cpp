#include <iostream>
#include <cmath>
using namespace std;

/*
Question: Implement Pow(x,n)
*/

float my_pow(float x, int n) {
	if (n == 0) {
		return 1;
	}

	float val = my_pow(x, n / 2);

	if ((n % 2) == 0) {
		return val * val;
	}
	else {
		if (n > 0) {
			return x * val * val;
		}
		else {
			return val * val / x;
		}
	}
}

int main() {
	cout << my_pow(2, 0) << endl;
	cout << my_pow(2, 2) << endl;
	cout << my_pow(2, 3) << endl;
	cout << my_pow(2, -3) << endl;
	cout << my_pow(2, -2) << endl;

	return 0;
}