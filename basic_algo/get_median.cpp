#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <ctime> 
using namespace std;

/*
Question: Find median of an unsorted array.

Solution: is based on Qickselect

Time Complexity:
Expected: O(n)
Worst Case: O(n^2)

Possible Improvement:
- median of medians -> Worst Case: O(n)
*/

// pick random element (pivot) from vec and split into L (elements smaller pivot) and G (elements larger pivot)
int partition(vector<int> &vec, int left, int right) {
    int pivot_index = left + rand() % (right - left);
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

// Returns the n-th smallest element of list within left..right inclusive (i.e. n is zero-based). 
int quick_select(vector<int> &vec, int left, int right, int n) {
	if(left == right) {
		return vec[left];
	}	
	
	int pivot_index = partition(vec, left, right);
	
	if(pivot_index == n) {
		return vec[pivot_index];
	}
	else if(pivot_index < n) {
		return quick_select(vec, pivot_index + 1, right, n);
	}
	else if(pivot_index > n) {
		return quick_select(vec, left, pivot_index - 1, n);
	}
}

int get_median(vector<int> vec) {
	int n = vec.size() / 2;
	return quick_select(vec, 0, vec.size() - 1, n);
}

int get_median2(vector<int> vec) {
	int n = vec.size() / 2;

	nth_element(vec.begin(), vec.begin() + n, vec.end());
	return vec.at(n);
}

int main() {
	// your code goes here 

	srand(time(0));

	vector<int> numbers = { 9, 2, 4, 3, 8, 5, 7, 6, 1 };
	cout << get_median(numbers) << endl;
	cout << get_median2(numbers) << '\n' << endl;

	vector<int> numbers2 = { 6, 8, 2 };
	cout << get_median(numbers2) << endl;
	cout << get_median2(numbers2) << '\n' << endl;

	vector<int> numbers3 = { 1, 10, 5, 7 };
	cout << get_median(numbers3) << endl;
	cout << get_median2(numbers3) << '\n' << endl;

	vector<int> numbers4 = { 11, 3, 7, 8 };
	cout << get_median(numbers4) << endl;
	cout << get_median2(numbers4) << '\n' << endl;

	vector<int> numbers5 = { 3, 1 };
	cout << get_median(numbers5) << endl;
	cout << get_median2(numbers5) << endl;

	return 0;
}
