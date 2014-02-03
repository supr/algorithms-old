#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

/* Question:
A zero-indexed array A consisting of N integers is given. An equilibrium index of
this array is any integer P such that 0 <= P < N and the sum of elements of lower
indices is equal to the sum of elements of higher indices, i.e.
A[0] + A[1] + ... + A[P-1] = A[P+1] + ... + A[N-2] + A[N-1].

Sum of zero elements is assumed to be equal to 0. This can happen if P = 0 or if P = N-1.
For example, consider the following array A consisting of N = 7 elements:
A[0] = -7   A[1] =  1   A[2] = 5
A[3] =  2   A[4] = -4   A[5] = 3
A[6] =  0

P = 3 is an equilibrium index of this array, because:
A[0] + A[1] + A[2] = A[4] + A[5] + A[6]

P = 6 is also an equilibrium index, because:
A[0] + A[1] + A[2] + A[3] + A[4] + A[5] = 0
and there are no elements with indices greater than 6.

P = 7 is not an equilibrium index, because it does not fulfill the condition 0 <= P < N.

Write a function
int solution(const vector<int> &A);
that, given a zero-indexed array A consisting of N integers, returns any of its
equilibrium indices. The function should return -1 if no equilibrium index exists.

Assume that:
N is an integer within the range [0..10,000,000];
each element of array A is an integer within the range [-2,147,483,648..2,147,483,647].
For example, given array A such that
A[0] = -7   A[1] =  1   A[2] = 5
A[3] =  2   A[4] = -4   A[5] = 3
A[6] =  0
the function may return 3 or 6, as explained above.

Complexity:
expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage
required for input arguments).
Elements of input arrays can be modified.
*/

int equilibrium_index(const vector<int> &A) {
	// write your code in C++98
	int size = A.size();
	if (size == 0) {
		return -1;
	}

	vector<long long> left_sum(A.size());
	vector<long long> right_sum(A.size());
	long long sum1 = 0;
	long long sum2 = 0;

	for (int i = 0; i < A.size(); i++) {
		sum1 += A[i];
		left_sum[i] = sum1;
	}

	for (int i = A.size() - 1; i >= 0; i--) {
		sum2 += A[i];
		right_sum[i] = sum2;
	}

	for (int i = 0; i < left_sum.size(); i++) {
		if (left_sum[i] == right_sum[i]) {
			return i;
		}
	}

	return -1;
}

int main() {
	// your code goes here

	vector<int> A = { -7, 1, 5, 2, -4, 3, 0 };
	assert(equilibrium_index(A) == 3);

	vector<int> B = { 1, -1, 0 };
	assert(equilibrium_index(B) == 2);

	vector<int> C = {};
	assert(equilibrium_index(C) == -1);
	return 0;
}