#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

/*
Question: How to get the average from a stream of numbers at any time?
The average means the number closest to each number in the sequence. You
find the average by adding all of the numbers together, then dividing this total.

Time Complexity: O(1)
Space Complexity: O(1)
*/

class AverageFromStream {
private:
	int total;
	int count;
public:
	float get_average(int number) {
		total += number;
		count++;

		return total / static_cast<float>(count);
	}
};

int main() {
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	AverageFromStream a1;
	for (int i = 0; i < vec.size(); i++) {
		cout << a1.get_average(vec[i]) << ' ';
	}
	cout << endl;

	AverageFromStream a2;
	for (int i = vec.size() - 1; i >= 0; i--) {
		cout << a2.get_average(vec[i]) << ' ';
	}
	cout << endl;

	return 0;
}