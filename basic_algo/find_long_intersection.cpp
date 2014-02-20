#include <iostream>
#include <string>
using namespace std;

/* Question:
Find the longest intersection between two strings

e.g.
string1: hello
string2: bella
result:  ell
*/

pair<int,int> find_most_right_match(string &str1, string &str2, int i, int j) {
	int count = 0;
	
	while(i < str1.size() && j < str2.size()) {
		if(str1[i] == str2[j]) {
			i++;
			j++;
			count++;
		}
		else {
			break;
		}
	}
	
	return make_pair(count, i);
}

string find_long_intersection(string &str1, string &str2) {
	int longest_match = 0;
	int index_start = 0;
	int index_end = 0;
	
	for(int i = 0; i < str1.size(); i++) {
		for(int j = 0; j < str2.size(); j++) {
			if(str1[i] == str2[j]) {
				pair<int,int> p = find_most_right_match(str1, str2, i, j);
				
				if(p.first > longest_match) {
					longest_match = p.first;
					index_start = i;
					index_end = p.second;
				}
			}
		}
	}
	
	return str1.substr(index_start, index_end - index_start);
}

int main() {
	// your code goes here
	
	string str1 = "Apple";
	string str2 = "elppA";
	cout << find_long_intersection(str1, str2) << endl;
	
	return 0;
}
