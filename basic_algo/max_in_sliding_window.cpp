#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

/*
Given an array of numbers and a sliding window size, how do you get the maximum numbers in all sliding 
windows?
For example, if the input array is {2, 3, 4, 2, 6, 2, 5, 1} and the size of the sliding windows is 3, 
the output of maximums are {4, 4, 6, 6, 6, 5}

Sliding Windows in an Array		Maximums in Sliding Windows
[2,3,4],2,6,2,5,1				      4 
2,[3,4,2],6,2,5,1             4
2,3,[4,2,6],2,5,1             6
2,3,4,[2,6,2],5,1 				    6
2,3,4,2,[6,2,5],1 				    6
2,3,4,2,6,[2,5,1]				      5
*/

vector<int> maxInWindows(vector<int> maxi, unsigned int windowSize) {
	for(auto it = maxi.begin(); it != maxi.end(); it++) {
		*it = *max_element(it, it + windowSize);
		
		if(it + windowSize == maxi.end()) {
			break;
		}
	}
	
	maxi.resize(maxi.size() - windowSize + 1);
	return maxi;
}

int main() {
	// your code goes here
	
	vector<int> numbers = {2, 3, 4, 2, 6, 2, 5, 1};
	vector<int> maxi = maxInWindows(numbers, 3);
	
	for(auto value : maxi)
		cout << value << endl;
	
	return 0;
}
