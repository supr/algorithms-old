#include <stdio.h>
#include <string.h>

/* Question:
remove all spaces from a string

Solution:
- implemented in Ansi C
*/

void remove_space(char *str) {
	int total_index = 0;
	int len = strlen(str) - 1;

	for (int i = 0; i < len; i++) {
		if (str[i] != ' ') {
			str[total_index++] = str[i];
		}
	}
}

int main() {
	// your code goes here

	char str[] = "Hi how are you?";

	remove_space(str);

	printf("%s", str);

	return 0;
}