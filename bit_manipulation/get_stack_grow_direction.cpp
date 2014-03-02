#include <iostream>
using namespace std;

/* Question 
Write a function which determines if a stack grows up or downwards
*/

// true = stack grows upwards
// false = stack grows downwards
bool get_stack_growth_direction(int *p) {
	int i;
	
	if(!p) {
		get_stack_growth_direction(&i);
	}
	else if(&i > p) {
		return true;
	}
	else if(&i < p) {
		return false;
	}
}


int main() {
	// your code goes here
	
	bool dir = get_stack_growth_direction(NULL);
	if(dir) {
		cout << "stack grows upwards" << endl;
	}
	else {
		cout << "stack grows downwards" << endl; 
	}
	
	return 0;
}
