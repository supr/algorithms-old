#include <iostream>
using namespace std;

/*
Question:
Implement strstr() to Find a Substring in a String

Knuth Morris Pratt Algorithm (KMP) runs in O(n)
https://www.youtube.com/watch?v=SVKe7bvQ4Xk
*/

// complexity: O(n * m), n=length of str, m=length of search
char *strstr(char *str, const char *search) {
	unsigned int len = 0;
	bool found = false;
	
	if(!str || !search) {
		return NULL;
	}
	
	while(*str != '\0') {
		
		if(*str == *search) {
			len++;
			search++;
			
			found = true;
		}
		else {
			if(found) {
				search = search - len;
				len = 0;
			}
			
			found = false;
		}
		
		str++;
		
		if(*search == '\0') {
			return str - len;
		}
	}
	
	return NULL;
}

char *StrStr(const char *s1, const char *s2) {
  const char *a = s1;
  const char *b = s2;

  for (;;) {
    if (!*b) return (char *)s1;
    if (!*a) return NULL;
    if (*a++ == *b++) continue;
    a = ++s1;
    b = s2;
  }
}

int main() {
	// your code goes here
	
  char str[] = "This is a simple string";
  char *pch;
  pch = strstr(str, "simple");
  cout << pch << endl;
  	
	return 0;
}