#include <iostream>
#include <unordered_set>
#include <cassert>
using namespace std;

/* Question:
Write an efficient function that deletes characters from an ASCII
string. Use the prototype string removeChars( string str, string remove );
where any character existing in remove must be deleted from str. For example,
given a str of "Battle of the Vowels: Hawaii vs. Grozny" and a remove of
"aeiou", the function should transform str to “Bttl f th Vwls: Hw vs. Grzny”.
Justify any design decisions you make, and discuss the efficiency of your solution.
*/

string remove_chars(string str, string remove) {
  unordered_set<char> hs;
  int index = 0;
  
  for (int i = 0; i < remove.size(); i++) {
    hs.insert(remove[i]);
  }
  
  for (int i = 0; i < str.size(); i++) {
    auto it = hs.find(str[i]);
    if (it == hs.end()) {
      str[index] = str[i];
      index++;
    }
  }
  
  str.resize(index);
  
  return str;
}

int main() {
	// your code goes here

	string s = "Battle of the Vowels: Hawaii vs. Grozny";
	string remove = "aeiou";
	assert(remove_chars(s, remove) == "Bttl f th Vwls: Hw vs. Grzny");

	return 0;
}