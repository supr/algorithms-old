#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/* Question:
Write a code that prints out all the palindrome words in a string
*/

void findPalindrom(const string &str, int start, int i, int j, vector<string> &palindroms) {
  if(i < 0 || j >= str.size()) {
    return;
  }
  
  string candidate;
  if(start != -1) {
    candidate = str[start];
  }
  
  while(i >= 0 && j < str.size()) {
    if(str[i] == str[j]) {
      candidate = str[i] + candidate;
      candidate += str[j];
      
      palindroms.push_back(candidate);  
      
      i--;
      j++;
    }
    else {
      break;
    }
  }
}

vector<string> getAllPalindroms(string str) {
  vector<string> palindroms;
  
  for(int i = 0; i < str.size(); i++) {
    findPalindrom(str, -1, i, i+1, palindroms);
    findPalindrom(str, i+1, i, i+2, palindroms);
  }
  
  return palindroms;
}

int main() {
  // your code goes here
  
  vector<string> palindroms = getAllPalindroms("abcddcbaABCDEDCBA");
  for(auto str : palindroms) {
    cout << str << endl;
  }
  
  return 0;
}