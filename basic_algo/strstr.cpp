#include <iostream>
using namespace std;

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

int main() {
	// your code goes here
	
	char str[] = "This is a simple string";
  char *pch;
  pch = strstr(str, "simple");
  cout << pch << endl;
  	
	return 0;
}