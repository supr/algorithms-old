#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
Implement rotate function.
Clarification: with O(1) additional memory.

Solution: based on the block-swap algorithm.
*/

void shift_l(vector<int> &num) {
	int i = 1;
	int tmp = num[0];
	
	while(i < num.size()) {
		num[i - 1] = num[i];
		i++;
	}
	
	num[num.size() - 1] = tmp;
}

void shift_r(vector<int> &num) {
	int i = num.size() - 2;
	int tmp = num[num.size() - 1];
	
	while(i >= 0) {
		num[i + 1] = num[i];
		i--;
	}
	
	num[0] = tmp;
}

void my_rotate1(vector<int> &num, int pos) {
	if(pos > 0) {
		pos = pos % num.size();
			
		for(int i = 0; i < pos; i++) {
			shift_r(num);
		}
	}
	else {
		pos = abs(pos);
		pos = pos % num.size();
			
		for(int i = 0; i < pos; i++) {
			shift_l(num);
		}
	}
}

void my_reverse(vector<int> &vec, int start, int end) {
	int j = end;
	
	for(int i = start; i <= (start + end) / 2; i++) {
		swap(vec[i], vec[j]);
		j--;
	}
}

void my_rotate2(vector<int> &num, int pos) {
	bool rotate_left = false;
	int len = num.size();
	
	if(pos < 0) {
		rotate_left = true;
	}
	
	pos = abs(pos);
	pos = pos % num.size();
	
	if(rotate_left) {
		my_reverse(num, 0, pos-1);
		my_reverse(num, pos, len-1);
		my_reverse(num, 0, len-1);
	}
	else {
		my_reverse(num, 0, len-1-pos);
		my_reverse(num, len-pos, len-1);
		my_reverse(num, 0, len-1);
	}
}

int main() {
	vector<int> vec1 = {1, 1, 4, 7, 10, 13};
	vector<int> vec2 = {1, 1, 4, 7, 10, 13};
		
	for_each(vec1.begin(), vec1.end(), [](int val){ cout << val << ' ';});
	cout << '\n';
	for_each(vec2.begin(), vec2.end(), [](int val){ cout << val << ' ';});
	cout << '\n';
	
	my_rotate1(vec1, 2);
	my_rotate2(vec2, 2);
	
	for_each(vec1.begin(), vec1.end(), [](int val){ cout << val << ' ';});
	cout << '\n';
	for_each(vec2.begin(), vec2.end(), [](int val){ cout << val << ' ';});
	
	return 0;
}
