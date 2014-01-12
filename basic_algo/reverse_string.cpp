#include <stdio.h>
#include <string.h>

/* Question:
Implement a function void reverse(char* str) in C or C++ which reverses a nullterminated
string.
*/

void swap1(char *a, char *b) {
	char tmp = *b;
	*b = *a;
	*a = tmp;
}

void my_reverse1(char *str) {
	int j = strlen(str) - 1;

	for (int i = 0; i < strlen(str) / 2; i++) {
		swap1(&str[i], &str[j]);
		j--;
	}
}

void swap2(char *a, char *b) {
	char tmp = *b;
	*b = *a;
	*a = tmp;
}

void my_reverse2(char *str) {
	char *start = str;
	char *end = start + (strlen(start) - 1);

	for (int i = 0; i < strlen(str) / 2; i++) {
		swap2(start, end);
		start++;
		end--;
	}
}

int main() {
	// your code goes here

	char str1[] = "Hello";
	char str2[] = "Helloworld";

	my_reverse2(str1);
	my_reverse2(str2);

	printf("%s\n", str1);
	printf("%s\n", str2);

	my_reverse1(str1);
	my_reverse1(str2);

	printf("%s\n", str1);
	printf("%s\n", str2);

	return 0;
}