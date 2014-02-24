#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
Please implement a function that finds the intersection of two sorted arrays. Assume numbers 
in each array are unique. 
For example, if the two sorted arrays as input are {1, 4, 7, 10, 13} and {1, 3, 5, 7, 9}, the output is an intersection 
array with numbers {1, 7}. 

Solution:
- vector<int> get_intersection1(vector<int> &arr1, vector<int> &arr2): Complexity: O(m + n)
- vector<int> gget_intersection2(vector<int> &arr1, vector<int> &arr2): Complexity: O(m * log n)
*/

vector<int> get_intersection1(vector<int> &arr1, vector<int> &arr2) {
	vector<int> out;
	auto it1 = arr1.begin();
	auto it2 = arr2.begin();
	
	if(arr1.size() == 0 || arr2.size() == 0) {
		return out;
	}
	
	while(it1 != arr1.end() && it2 != arr2.end()) {
		if(*it1 < *it2) {
			it1++;
		}	
		else if(*it2 < *it1) {
			it2++;
		}
		
		if(*it1 == *it2) {
			out.push_back(*it1);
			it1++;
			it2++;
		}
		
		if(it1 == arr1.end() && *it1 < *it2) {
		   	break;
		}
		
		if(it2 == arr2.end() && *it2 < *it1) {
		   	break;
		}
	}
	
	return out;
}

vector<int> get_intersection2(vector<int> &arr1, vector<int> &arr2) {
	vector<int> out;
	
	if(arr1.size() == 0 || arr2.size() == 0) {
		return out;
	}
	
	if(arr1.size() > arr2.size()) {
		for(int i = 0; i < arr2.size(); i++) {
			auto it = find(arr1.begin(), arr1.end(), arr2[i]);
			if(it != arr1.end()) {
				out.push_back(arr2[i]);
			}
		}
	}
	else {
		for(int i = 0; i < arr1.size(); i++) {
			auto it = find(arr2.begin(), arr2.end(), arr1[i]);
			if(it != arr2.end()) {
				out.push_back(arr1[i]);
			}
		}	
	}
	
	return out;
}

int main() {
	// your code goes here
	
	vector<int> vec1 = {1, 4, 7, 10, 13};
	vector<int> vec2 = {1, 3, 5, 7, 9, 11, 12, 13};
	
	vector<int> intersec1 = get_intersection1(vec1, vec2);
	for_each(intersec1.begin(), intersec1.end(), [](int val) { cout << val << ' '; });
	
	cout << '\n';
	
	vector<int> intersec2 = get_intersection2(vec1, vec2);
	for_each(intersec2.begin(), intersec2.end(), [](int val) { cout << val << ' '; });
	
	return 0;
}
