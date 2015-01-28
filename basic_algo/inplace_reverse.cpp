#include <iostream>
#include <string>
using namespace std;

/* 
Question:
Inplace reverse a sentence 

You given a sentence of english words and spaces between them. 
Nothing crazy: 
1) no double spaces 
2) no empty words 
3) no spaces at the ends of a sentence


void inplace_reverse(char* arr, int length) {
    // your solution
}
Example: 
input "I wish you a merry Christmas" 
output "Christmas merry a you wish I" 

Constrains: O(1) additional memory
*/

void myReverse(string &str, int start, int end) {
  int j = end;

  for (int i = start; i <= (start + end) / 2; i++) {
    swap(str[i], str[j]);
    j--;
  }
}

void inplace_reverse(string &input) {
  myReverse(input, 0, input.size()-1);
  
  int start = 0;
  
  for (int i = 0; i <= input.size(); i++) {
    if (input[i] == ' ' || i == input.size()) {
      myReverse(input, start, i-1);
      start = i+1;
    }
  }
}

int main() {
  // your code goes here
  
  string s = "I wish you a merry Christmas";
  inplace_reverse(s);
  cout << s << endl;
  
  return 0;
}