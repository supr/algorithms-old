#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Question:
Implement rotate function for forward-only iterators. 

Clarification: with O(1) additional memory. Rotate semantics should be that 
of std::rotate. 
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

void my_rotate2(vector<int> &num, int pos) {
	bool rotate_left = false;

	if(pos < 0) {
		rotate_left = true;
	}
	
	pos = abs(pos);
	pos = pos % num.size();

	if(rotate_left) {
		int index_i = 0;
		int index_j = pos;

		while(index_j < num.size()) {
			swap(num[index_i], num[index_j]);
			index_i++;
			index_j++;
		}		
	}
	else {	
		int last_index = num.size() - 1;
		int index_i = last_index;
		int index_j = last_index - pos;

		while(index_j >= 0) {
			swap(num[index_i], num[index_j]);
			index_i--;
			index_j--;
		}
	}
}

int main() {
	vector<int> vec1 = {1, 1, 4, 7, 10, 13};
	vector<int> vec2 = {1, 1, 4, 7, 10, 13};

	for_each(vec1.begin(), vec1.end(), [](int val){ cout << val << ' ';});
	cout << '\n';
	for_each(vec2.begin(), vec2.end(), [](int val){ cout << val << ' ';});
	cout << '\n';

	my_rotate1(vec1, -2);
	my_rotate2(vec2, -2);

	for_each(vec1.begin(), vec1.end(), [](int val){ cout << val << ' ';});
	cout << '\n';
	for_each(vec2.begin(), vec2.end(), [](int val){ cout << val << ' ';});

	return 0;
}
