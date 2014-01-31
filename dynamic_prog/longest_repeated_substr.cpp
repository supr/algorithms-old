#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*Question:
Longest Repeated Substring (LRS):

Brute Force Solution: Brute force Immediately suggest itself: we compare the substring starting at each string position i with the
substring starting at each other starting position j, keeping the track of longest match found. This code is not useful for long strings
because it's running time is atleast quadratic in the length of the string.

Suffix sort Solution: Make an array of strings that consist of the suffixes of s and then we sort this array.
The key to the algorithm is that every substring appears somewhere as a prefix of one of the suffixes in the array.
After sorting, the longest repeated substrings will appear in adjacent positions in the array. Thus we can make a single pass through
the sorted array, keeping track of longest matching prefixes between adjacent strings.
*/

// What is the longest substring that appears at least twice in a given string?
class LRS
{
public:
	int len;
	vector<string> suffixes;

	void build_suffix_array(string &str)
	{
		len = str.size();
		for (int i = 0; i < len; i++)
		{
			//cout << str.substr(i, len - i) << endl;
			suffixes.push_back(str.substr(i, len - i));
		}
		sort(suffixes.begin(), suffixes.end());
		vector<string>::iterator itr;
		for (itr = suffixes.begin(); itr != suffixes.end(); ++itr)
		{
			//cout << "sorted string : " << *itr << endl;
		}
	}
	int length() { return len; }
	string select(int index) { return suffixes[index]; }
	int index(int index) { return len - suffixes[index].size(); }

	int lcp(int index)
	{
		return lcp(suffixes[index], suffixes[index - 1]);
	}

	int lcp(string &str1, string &str2)
	{
		int N = min(str1.size(), str2.size());
		for (int i = 0; i < N; i++)
		{
			if (str1.at(i) != str2.at(i)) return i;
		}
		return N;
	}

	string lrs(string &str) {
		build_suffix_array(str);

		// Calculate the Longest repeated substring
		string lrs;
		for (int i = 1; i < str.size(); ++i) {
			int len = lcp(i);
			if (len > lrs.size()) {
				lrs = select(i).substr(0, len);
			}
		}

		return lrs;
	}
};

int main() {
	LRS longest_rep_str;
	string str = "banana";
	cout << longest_rep_str.lrs(str) << endl;
}