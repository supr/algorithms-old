#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
An unsorted array is given and we need to find top k elements in an efficient way 
and we cannot sort the array.

Solution:
Option 1: Using a Priority Queue (heap). Complexity O(n log k)
Option 2: Using Selection algorithm (first finding kth largest element and then 
sorting the elements < k). Complexity O(k log k).
*/

int rand_select(vector<int> &vec, int left, int right) {
	int r = left + rand() % (right - left);
	int pivot = vec[r];
	
	while(true) {
		while(vec[left] < pivot) { left++; }
		while(vec[right] > pivot) { right--; }
		
		if(left > right) {
			break;
		}
		
		swap(vec[left++], vec[right--]);
	}	
	
	return left;
}

int quick_select(vector<int> &vec, int left, int right, int k) {
	if(left == right) {
		return vec[left];
	}
	
	int pivot = rand_select(vec, left, right);
	if(pivot == k) {
		return vec[k];
	}
	else if(pivot < k) {
		return quick_select(vec, pivot+1, right, k); 
	}
	else if(pivot > k) {
		return quick_select(vec, left, pivot-1, k); 
	}
}

vector<int> find_top_k_elements(vector<int> &vec, int k) {
	vector<int> out;
	
	for(int i = 0; i < k; i++) {
		quick_select(vec, 0, vec.size() - 1, i);
		out.push_back(vec[i]);
	}
	
	return out;
}

int main() {
	// your code goes here
	
	vector<int> vec = {5,7,1,9,3,7,3,11,16};
	vector<int> top_k_elements = find_top_k_elements(vec, 3);
	
	for_each(top_k_elements.begin(), top_k_elements.end(), [](int val) { cout << val << ' '; });
	
	return 0;
}
