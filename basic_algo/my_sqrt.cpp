#include <iostream>
#include <cmath>
using namespace std;

/*
Question: Implement int sqrt(int x).
Compute and return the square root of x.

Theory: http://helloacm.com/coding-exercise-implement-integer-square-root-c-online-judge/

This algorithm is implemented in two versions:
- based on newton method
- based on binary search
*/

/*
xn = sqrt(a)
xn^2 - a = 0
f(x) = x^2 - a
f(x+1) = f(x) - (f(x+1) * f(x+1) - a) / (2 * f(x+1))
*/
float my_sqrt_newton(float a) {
	float eps = 0.00001;
	float xn_1 = a;
	float xn = 0;

	if (a < 0) {
		return -1;
	}

	while (eps < abs(xn_1 - xn)) {
		xn = xn_1;
		xn_1 = xn - (xn_1 * xn_1 - a) / (2 * xn_1);
	}

	return xn;
}

float my_sqrt_bin_search(float a) {
	float end = a;
	float start = 0;
	float eps = 0.00001;

	if (a < 0) {
		return -1;
	}

	if (a < 1) {
		end = 1.0;
	}

	while (abs(end - start) > eps) {
		float mid = start + (end - start) / 2;
		float sqr = mid * mid;

		if (sqr > a) {
			end = mid;
		}
		else if (sqr <= a) {
			start = mid;
		}
	}

	return start;
}

int main() {
	cout << my_sqrt_newton(16) << endl;
	cout << my_sqrt_bin_search(16) << endl;

	cout << my_sqrt_newton(9.5) << endl;
	cout << my_sqrt_bin_search(9.5) << endl;

	return 0;
}
