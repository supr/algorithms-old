#include <stdio.h>
#include <string.h>

/* Question:
Implement an algorithm to determine if a string has all unique characters. What if
you cannot use additional data structures.

Solution:
- Implemente in Ansi C
*/

bool hash_unique_chars(char *str) {
	const int table_size = 255;
	int table[table_size] = { 0 };
	int len = strlen(str);

	for (int i = 0; i < len; i++) {
		if (table[str[i] - 'A'] == 1) {
			return false;
		}
		else {
			table[str[i] - 'A']++;
		}
	}

	return true;
}

int main() {
	// your code goes here

	char str1[] = "Hello";
	char str2[] = "Hansi";

	bool result1 = hash_unique_chars(str1);
	if (result1) {
		printf("The string \"%s\" has unique characters\n", str1);
	}
	else {
		printf("The string \"%s\" does not have unique characters\n", str1);
	}

	bool result2 = hash_unique_chars(str2);
	if (result2) {
		printf("The string \"%s\" has unique characters\n", str2);
	}
	else {
		printf("The string \"%s\" does not have unique characters\n", str2);
	}

	return 0;
}