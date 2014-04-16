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
	vector<int> move;
	
	// left
	if(pos < 0) {
		pos = abs(pos);
		pos = pos % num.size();
		int index = 0;
				
		while(index < pos) {
			move.push_back(num[index++]);
		}
		
		num.erase(num.begin(), num.begin() + pos);
		num.insert(num.begin() + num.size(), move.begin(), move.end());
	}	
	// right
	else {
		pos = pos % num.size();
		int index = num.size() - pos;
		
		while(index < num.size()) {
			move.push_back(num[index++]);
		}
		
		num.erase(num.begin() + num.size() - pos, num.begin() + num.size());
		num.insert(num.begin(), move.begin(), move.end());
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
