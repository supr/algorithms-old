#include <iostream>
#include <string>
using namespace std;

/* Question:
Find the longest palindrome in a input string.

Example - aaabbaaaccdeqjncsdddmmmkkkmmmddd

Answer - dddmmmkkkmmmddd
*/

// searches for the largest palindrome for a given middle point left, right
// compares each character on the left with the character on the right side
void palindrome_search(const string &s, int middle_index, int l, int r, string &longest_pal) {
  bool found = false;
  string pal;
  
  if(middle_index != -1) {
    pal = s[middle_index];
  }
  
  while(l >= 0 && r < s.size()) {
    if(s[l] == s[r]) {
      pal = pal + s[r];
      pal = s[l] + pal;
      found = true;
      l--;
      r++;
    }
    else {
      break;
    }
  }
  
  if(found && pal.size() > longest_pal.size()) {
    longest_pal = pal;
  }
}

string find_longest_palindrome(const string &str) {
  string longest_pal;
  
  for(int i = 0; i < str.size(); i++) {
    // pair element in the middle of the palindrome
    // e.g. 1221
    if(i < str.size() - 1 && str[i] == str[i+1]) {
      palindrome_search(str, -1, i, i+1, longest_pal);
    } 
    // single element in the middle of the palindrome
    // e.e.g 22122
    if(i < str.size() - 2 && str[i] == str[i+2]) {
      palindrome_search(str, i+1, i, i+2, longest_pal);
    }
  }
  
  return longest_pal;
}

int main() {
  // your code goes here
  
  cout << find_longest_palindrome("aaabbaaaccdeqjncsdddmmmkkkmmmddd") << endl;
  
  return 0;
}