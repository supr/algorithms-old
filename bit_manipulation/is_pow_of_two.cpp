#include <iostream>
#include <cassert>
using namespace std;

/* Question:
Check if an integer number is a power of two.
*/

/*
If x is a power of two, it doesn't have any bits in common with x-1, since it
consists of a single bit on. Any positive power of two is a single bit, using
binary integer representation.

This means that we test if x-1 and x doesn't share bits with the and operator.

Of course, if x is zero (not a power of two) this doesn't hold, so we add an
explicit test for zero with xx && expression.

Negative powers of two (0.5, 0.25, 0.125, etc) could share this same property
in a suitable fraction representation. 0.5 would be 0.1, 0.250 would be 0.01,
0.125 would be 0.001 etc.
*/

int is_pow_of_two(int number) {
	if(number < 0) {
		number = ~number;
		number += 1;
	}
	
	return number && !(number & (number - 1));
}

int main() {
	// your code goes here
	
	assert(is_pow_of_two(2) == 1);
	assert(is_pow_of_two(1) == 1);
	assert(is_pow_of_two(-2) == 1);
	assert(is_pow_of_two(5) == 0);
	
	return 0;
}
