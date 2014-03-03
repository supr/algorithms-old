#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/* Question:
Given an array with N - 2 elements (two missing) from 1 to N, find the two 
missing elements in linear time and constant memory usage.
*/

unsigned int factorial(unsigned int n) {
    unsigned int ret = 1;
    for(unsigned int i = 1; i <= n; ++i)
        ret *= i;
    return ret;
}

// sum (arr) = N * (N+1) / 2
// product (arr) = p * x * y = N!
// product_x_y = N! / p
pair<int,int> find_missing_two_elements(const vector<int> &vec) {
	int total_sum = vec.back() * (vec.back() + 1) / 2;
	int total_product = factorial(vec.back());
	int sum_x_y = 0;
	int product_x_y = 0;
	int p = 1;
	
	for(int i = 0; i < vec.size(); i++) {
		sum_x_y += vec[i];
		p *= vec[i];
	}
	
	sum_x_y = total_sum - sum_x_y;
	product_x_y = total_product / p;
	
	int b = sum_x_y;
	int y = (-b + sqrt(b * b - 4 * -1 * -product_x_y)) / 2 * -1;
	int x = sum_x_y - y;
	
	return make_pair(x, y);	
}

int main() {
	// your code goes here
	
	vector<int> vec = {1, 4, 5};
	
	pair<int,int> p = find_missing_two_elements(vec);
	cout << p.first << " " << p.second << endl;
	
	return 0;
}
