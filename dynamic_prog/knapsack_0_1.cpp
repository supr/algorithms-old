#include <iostream>
#include <vector>
#include <array>
using namespace std;

/* Question:
Given a Knapsack of maximum capacity M and weight w1,w2,w3,...wn
and benefits b1,b2,b3,...bn find which weight to choose so as to
maximize the benefit

weight  2 3 4 5
benefit 3 4 5 6

best benefit: w1 + w2 = 3 + 4 = 7

B(i, w) = B(i-1, w)	wi > M
   __{ = B(i-1, w)		   not choosing ith item
max  { = bi + B(t-1,w-wi)	   choosing ith item

B(0,w) = 0
B(i,0) = 0
*/

const int n = 4;
const int W = 5;

int Knapsack(std::array<std::array<int, W + 1>, n + 1> &A, std::vector<int> v, std::vector<int> w) {
	// initialization
	for (int w = 0; w <= W; w++) {
		A[0][w] = 0;
	}

	// main loop
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= W; j++) {
			if (w[i - 1] > j) {
				A[i][j] = A[i - 1][j];
			}
			else {
				A[i][j] = max(A[i - 1][j], v[i - 1] + A[i - 1][j - w[i - 1]]);
			}
		}
	}

	return A[n][W];
}

int main() {
	// your code goes here

	// Knapsack Problem
	// Time Complexity: O(nW), Space Complexity: O(nW)

	// Values (stored in array v)
	// Weights (stored in array w)
	// Number of distinct items (n)
	// Knapsack capacity (W)

	std::vector<int> v = { 3, 4, 5, 6 }; ////{10, 4, 7};
	std::vector<int> w = { 2, 3, 4, 5 }; //{4, 2, 3};
	//columns //rows
	std::array<std::array<int, W + 1>, n + 1> A;

	int result = Knapsack(A, v, w);
	cout << "result: " << result << endl;

	// display 2d array A
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= W; j++) {
			cout << A[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}