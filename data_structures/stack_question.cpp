#include <stdio.h>



/* Question
What is the output of the following code
*/

void foo(void) {
    
	int a;
    
	printf("%d\n", a++);

}



void bar(void) {
    
	int b = 42;

}



int main(void) {
    
	bar();
    
	foo();
    
	foo();

	return 0;

}