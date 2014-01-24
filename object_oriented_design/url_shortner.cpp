#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
Write a URL shortner (like tinyurl) . Take a URL as input & return a shortened URL. Another requirement is that we want to make our URLs as 
different as possible, so that successive calls return very different URIs
This is to ensure that small typo errors do not lead to users getting to a valid URL, but rather throwing up an error page.
*/

string encode(int num) {
	static char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	vector<char> sb;
	const size_t base = sizeof(alphabet);

	while (num > 0) {
		size_t index = num % base;

		sb.push_back(alphabet[index]);
		num /= base;
	}

	string result = alphabet;

	reverse_copy(sb.begin(), sb.end(), result.begin());

	result[sb.size()] = '\0';

	return result;
}

int main() {
	// your code goes here

	cout << encode(1000) << endl;

	return 0;
}