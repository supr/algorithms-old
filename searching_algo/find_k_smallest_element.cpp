#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/* Question:
An unsorted array is given and we need to find top k elements in an efficient way 
and we cannot sort the array.

Solution:
Option 1: Using a Priority Queue (heap). Complexity O(n log k)
Option 2: Using Selection algorithm (first finding kth largest element and then 
sorting the elements < k). Complexity O(k log k).
*/

int partition(vector<int> &vec, int left, int right) {
    int pivot_index = left + rand() % (right - left + 1);
    int pivot = vec[pivot_index];

    swap(vec[pivot_index], vec[right]);  // Move pivot to end
    int store_index = left;
    
    for(int i = left; i < right; i++) {
    	if(vec[i] <= pivot) {
            swap(vec[store_index], vec[i]);
            store_index++;
    	}
    }
    
    swap(vec[right], vec[store_index]);  // Move pivot to its final place
    return store_index;
}

int quick_select(vector<int> &vec, int left, int right, int k) {
    if (left == right) { 
        return vec[left];
    }

    int pivot_index = partition(vec, left, right);
    
    // The pivot is in its final sorted position
    if(k == pivot_index) {
    	return vec[k];
    }
    else if(k < pivot_index) {
    	return quick_select(vec, left, pivot_index - 1, k);
    }
    else {
        return quick_select(vec, pivot_index + 1, right, k);
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

priority_queue<int, vector<int>, std::less<int>> find_k_min_numbers(vector<int> &vec, int k) {
	priority_queue<int, vector<int>, std::less<int>> pq;

	for (int i = 0; i < vec.size(); i++) {
		if (pq.size() < k) {
			pq.push(vec[i]);
		}
		else {
			if (pq.top() > vec[i]) {
				pq.pop();
				pq.push(vec[i]);
			}
		}
	}

	return pq;
}

int main() {
	// your code goes here
	
	srand(time(0));
	
	vector<int> vec = {5,7,1,9,3,7,3,11,16,1};
	vector<int> top_k_elements = find_top_k_elements(vec, 3);
	deque<int> top_k_elements2;
	
	for_each(top_k_elements.begin(), top_k_elements.end(), [](int val) { cout << val << ' '; });
	
	cout << endl;
	
	priority_queue<int, vector<int>, std::less<int>> pq = find_k_min_numbers(vec, 3);

	while (!pq.empty()) {
		top_k_elements2.push_front(pq.top());
		pq.pop();
	}
	
	for_each(top_k_elements2.begin(), top_k_elements2.end(), [](int val) { cout << val << ' '; });
	
	return 0;
}
