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

Idea:
Long URL: "http://www.example.org/abcdef". 
Instead of "abcdef" there can be any other string with six characters containing a-z, A-Z and 0-9. 
That makes 56~57 billion possible strings.

I have a database table with three columns:
id, integer, auto-increment
long, string, the long URL the user entered
short, string, the shortened URL (or just the six characters)

insert the long URL into the table. Then I would select the auto-increment value for "id" and build a hash of it. 
This hash should then be inserted as "short".

For "http://www.google.de/" I get the auto-increment id 239472. Then I do the following steps:

Think of an alphabet we want to use. In your case that's [a-zA-Z0-9]. It contains 62 letters.
Take an auto-generated, unique numerical key (the auto-incremented id of a MySQL table for example).

For this example I will use 125 (125 with a base of 10).

Now you have to convert 125 to X_62 (base 62).

125 = 2×62^1 + 1×62^0 = [2,1]

Now map the indices 2 and 1 to your alphabet. This is how your mapping (with an array for example) could look like:

0  -> a
1  -> b
...
25 -> z
...
52 -> 0
61 -> 9

With 2 -> c and 1 -> b you will receive cb62 as the shortened URL.
http://shor.ty/cb

TODO: 
use big numbers instead of unsigned long long
*/

class URLShortner {
private:
	vector<char> alphabet;
	size_t base;
	
public:
	URLShortner(std::string list): alphabet(list.begin(), list.end()), 
	                               base(list.length()) {}

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
