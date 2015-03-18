#include <iostream>
using namespace std;

/*
Question:
Implement strcmp function of stdlib.h library without using any 
standard library.
*/

int strcmp (const char * str1, const char * str2) {
  char *s1 = (char*)str1;
  char *s2 = (char*)str2;
  
  while (*s1 == *s2) {
    s1++;
    s2++;
  }
  
  if (*s2 == '\0') {
    return 0;
  }
  else if (*s1 < *s2) {
    return -1;
  }
  
  return 1;
}

int main() {
  // your code goes here
  
  cout << strcmp("helloworld", "hello") << endl;
  
  return 0;
}