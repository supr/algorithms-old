#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

/* Question:
Remove duplicate characters in a given string keeping only the first occurrences. 
For example, if the input is ‘tree traversal’ the output will be ‘tre avsl’.
*/

string remove_duplicate_chars(const string &str) {
	unordered_map<char, int> ht;
	string out;
	
	for(int i = 0; i < str.size(); i++) {
		auto it = ht.find(str[i]);
		
		if(it == ht.end()) {
			ht.insert(make_pair(str[i], 1));
		}
		else {
			it->second++;
		}
	}
	
	for(int i = 0; i < str.size(); i++) {
		auto it = ht.find(str[i]);
		
		if(it == ht.end()) {
			out += str[i];
		}
		else {
			if(it->second != 0) {
				out += str[i];
			}
			
			if(it->second > 1) {
				it->second = 0;
			}
		}
	}
	
	return out;
}

int main() {
	// your code goes here
	
	cout << remove_duplicate_chars("tree traversal") << endl;
	
	return 0;
}
