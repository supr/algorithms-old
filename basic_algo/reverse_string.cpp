#include <stdio.h>
#include <string.h>
using namespace std;

/* Question:
Implement a function void reverse(char* str) in C or C++ which reverses a nullterminated
string.

The solution is implemented in Ansi C
*/

void swap(char &a, char &b) {
	char tmp = b;
	b = a;
	a = tmp;
}

void my_reverse(char *str) {
	int j = strlen(str) - 1;

	for (int i = 0; i < (strlen(str) - 1) / 2.0; i++) {
		swap(str[i], str[j]);
		j--;
	}
}

int main() {
	// your code goes here

	char str1[] = "Hello";
	char str2[] = "Helloworld";

	my_reverse(str1);
	my_reverse(str2);

	printf("%s\n", str1);
	printf("%s\n", str2);

	return 0;
}