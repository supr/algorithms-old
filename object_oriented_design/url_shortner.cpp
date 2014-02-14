#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

/* Question:
Write a URL shortner (like tinyurl) . Take a URL as input & return a shortened URL. Another 
equirement is that we want to make our URLs as different as possible, so that successive calls 
return very different URIs. This is to ensure that small typo errors do not lead to users getting 
to a valid URL, but rather throwing up an error page.

TODO: use big numbers instead of unsigned long long
*/

class URLShortner {
private:
	vector<char> alphabet;
	size_t base;
	
public:
	URLShortner(std::string list)
	  : alphabet(list.begin(), list.end())
	  , base(list.length())
		{ }

	string encode(unsigned long long int num) {
		vector<char> sb;
	
		while (num > 0) {
			size_t index = num % base;
	
			sb.push_back(alphabet[index]);
			num /= base;
		}
	
		string result(sb.cbegin(), sb.cend());
		
		reverse_copy(sb.begin(), sb.end(), result.begin());
	
		return result;
	}
	
	int alphabet_indexof(char s) {
	    int index = -1;
	    
	    auto it = std::find(alphabet.begin(), alphabet.end(), s);
		if (it != alphabet.end()) {
  			index = std::distance(alphabet.begin(), it);
		}
		
		return index;
	}
	
	unsigned long long int decode(const string &str) {
		unsigned long long int num = 0;
	
	    for(int i = 0; i < str.size(); i++) {
	    	int index = alphabet_indexof(str[i]);
	    	assert(index != -1);
	    	num = num * base + alphabet_indexof(str[i]);
	    }
	
	    return num;
	}
};

int main() {
	// your code goes here

	URLShortner s{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
	
	unsigned long long int id = s.decode("googledcom");
	cout << id << endl;
	string url_string1 = s.encode(id);
	cout << url_string1 << endl;
	
	string url_string2 = s.encode(12345);
	cout << url_string2 << endl;
	cout << s.decode(url_string2) << endl;
	
	return 0;
}
