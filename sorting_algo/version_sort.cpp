#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <limits>
using namespace std;

/* Question:
Given a vector of strings representing version numbers. 
Sort the version numbers from the lowest to the highest version number.
*/

typedef struct mycomparator {
	bool operator()(const std::string &a, const std::string &b) {
		stringstream ss1;
		stringstream ss2;
		double num1 = 0;
		double num2 = 0;

		ss1 << a;
		ss2 << b;

		ss1 >> num1;
		ss2 >> num2;

		return num1 < num2;
	}
}mycomparator;

vector<string> version_sort(vector<string> &vec) {
	int max_digits_after_dot = numeric_limits<int>::min();

	// get most right dot pos for zero padding
	for (int i = 0; i < vec.size(); i++) {
		int dot_index = vec[i].find('.');

		if (dot_index != string::npos) {
			dot_index = vec[i].size() - 1 - dot_index;

			if (dot_index > max_digits_after_dot) {
				max_digits_after_dot = dot_index;
			}
		}
	}

	// make strings equally long, fillup with zeros after the '.'
	for (int i = 0; i < vec.size(); i++) {
		int dot_index = vec[i].find('.');

		if (dot_index != string::npos) {
			int dot = vec[i].size() - 1 - dot_index;

			// zero padding
			while (dot < max_digits_after_dot) {
				vec[i].insert(vec[i].begin() + dot_index + 1, '0');
				dot++;
			}
		}
	}

	// sort strings by increasing number
	std::sort(vec.begin(), vec.end(), mycomparator());

	// erase padded zeros
	for (int i = 0; i < vec.size(); i++) {
		int dot_index = vec[i].find('.');
		int pos_last = vec[i].find_first_of('0', dot_index + 1);

		if (pos_last != string::npos) {
			vec[i].erase(dot_index + 1, pos_last - dot_index);
		}
	}

	return vec;
}

int main() {
	// your code goes here

	vector<string> versions = { "1.22", "1.2", "2.2", "1.12", "01.13", "2" };

	versions = version_sort(versions);
	for_each(versions.begin(), versions.end(), [](string s) { cout << s << endl; });

	return 0;
}