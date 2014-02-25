#include <iostream>
using namespace std;

/* Question: 
Write a C function that determines whether a computer is big-endian
or little-endian.
*/

bool is_little_endian() {
	union {
		int integer;
		char single_byte;
	}endian_test;
	
	endian_test.integer = 0x1020;
	
	if(endian_test.single_byte == 0x20) {
		return true;
	}
	
	return false;
}

int main() {
	// your code goes here
	
	cout << is_little_endian() << endl;
	
	return 0;
}
