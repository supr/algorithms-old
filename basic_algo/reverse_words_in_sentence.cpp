#include <iostream>
#include <string>
using namespace std;

void reverse_word(string &word, int start, int end) {
	int j = end;

	for (int i = start; i <= (start + end) / 2; i++) {
		swap(word[i], word[j]);
		j--;
	}
}

//   "--------- "my career stack" ---------" 
//to "--------- "ym reerac kcats" ---------"
void reverse_words_sentence(string &sentence) {
	bool enable_reversing = false;
	int start = 0;
	int end = 0;

	for (int i = 0; i < sentence.size(); i++) {
		if (!enable_reversing && sentence[i] == '\"') {
			enable_reversing = true;
			start = i + 1;
		}
		else if (sentence[i] == '\"') {
			enable_reversing = false;
			end = i - 1;
		}

		if (enable_reversing) {
			if (sentence[i] == ' ') {
				reverse_word(sentence, start, i - 1);
				start = i + 1;
			}
		}
	}

	reverse_word(sentence, start, end);
}

int main()
{
	// your code goes here

	string s = "--------- \"my career stack\" ---------";

	reverse_words_sentence(s);

	cout << s << endl;

	return 0;
}