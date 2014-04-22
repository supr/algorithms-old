#include <iostream>
#include <string>
using namespace std;

/*
How do you reverse the order of words in a sentence, but keep words themselves unchanged? 
Words in a sentence are separated by blanks. For instance, the reversed output should be 
"student. a am I" when the input is "I am a student.".
*/

void reverse(string &vec, int start, int end) {
	int j = end;
	
	for(int i = start; i <= start + (end - start) / 2; i++) {
		swap(vec[i], vec[j]);
		j--;
	}	
}

void reverse_words(string &sentence) {
	int start = 0;
	reverse(sentence, 0, sentence.size() - 1);
	
	for(int i = 0; i <= sentence.size(); i++) {
		if(sentence[i] == ' ' || i == sentence.size()) {
			reverse(sentence, start, i-1);
			start = i+1;
		} 
	}
}

int main() {
	// your code goes here
	
	string s = "I am a student.";
	reverse_words(s);
	
	cout << s << endl;
	
	return 0;
}
