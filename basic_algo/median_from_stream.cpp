#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

/*
Question: How to get the median from a stream of numbers at any time?
The median is middle value of numbers. If the count of numbers is even, the
median is defined as the average value of the two numbers in middle

Time Complexity: O(log(n))
Space Complexity: O(n)
*/

class MedianFromStream {
private:
	// stores all numbers smaller than the median
	priority_queue<int, vector<int>, std::less<int>> pq_min;
	// stores all number greater than the median
	priority_queue<int, vector<int>, std::greater<int>> pq_max;

public:
	float get_median(int number) {
		if (pq_min.size() == 0) {
			pq_min.push(number);
		}
		else if (pq_max.size() == 0) {
			pq_max.push(number);

			if (pq_max.top() < pq_min.top()) {
				int tmp = pq_min.top();
				pq_min.pop();
				pq_min.push(pq_max.top());
				pq_max.pop();
				pq_max.push(tmp);
			}
		}
		else {
			// check if we need to insert the new number into the min heap
			// the min heap stores the largest number in the top
			if (number <= pq_min.top()) {
				// check if the min heap size is larger than max heap size
				// in this case we need to shift the top element from the min heap to the max heap
				if (pq_min.size() > pq_max.size()) {
					int largest_min = pq_min.top();
					pq_min.pop();
					pq_max.push(largest_min);
				}

				pq_min.push(number);
			}
			// check if we need to insert the new number into the max heap
			// the max heap stores the smallest number in the top
			else if (number >= pq_max.top()) {
				// check if the max heap size is larger than min heap size
				// in this case we need to shift the top element from the max heap to the min heap
				if (pq_max.size() > pq_min.size()) {
					int smallest_max = pq_max.top();
					pq_max.pop();
					pq_min.push(smallest_max);
				}

				pq_max.push(number);
			}
		}

		// if min heap and max heap have the same size -> median is the average of both top elements
		if (pq_min.size() == pq_max.size()) {
			return (pq_min.top() + pq_max.top()) / 2.0;
		}
		// if min heap size is larger than the max heap -> median is the top element of min heap
		else if (pq_min.size() > pq_max.size()) {
			return pq_min.top();
		}
		// if max heap size is larger than the min heap -> median is the top element of max heap
		return pq_max.top();
	}
};

int main() {
	vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	MedianFromStream m1;
	for (int i = 0; i < vec.size(); i++) {
		cout << m1.get_median(vec[i]) << ' ';
	}
	cout << endl;

	MedianFromStream m2;
	for (int i = vec.size() - 1; i >= 0; i--) {
		cout << m2.get_median(vec[i]) << ' ';
	}
	cout << endl;

	return 0;
}