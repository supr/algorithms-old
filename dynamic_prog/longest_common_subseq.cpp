#include <iostream>
#include <array>
using namespace std;

/* Question:
Given two sequences, find the length of longest subsequence present in both of them.

Example:
input strings "AXYT" and "AYZX"

Overlapping Subproblems:
					lcs("AXYT", "AYZX")
					/                 \
		lcs("AXY", "AYZX")            lcs("AXYT", "AYZ")
		/            \                  /               \
lcs("AX", "AYZX") lcs("AXY", "AYZ")   lcs("AXY", "AYZ") lcs("AXYT", "AY")

Complexity:
O(m * n)
*/

const int m = 6;
const int n = 8;

array<array<int, n + 1>, m + 1> longest_common_subseq(array<int, m + 1> &X, array<int, n + 1> &Y) {
	array<array<int, n + 1>, m + 1> LCS;

	for (int i = 0; i <= m; i++) {
		LCS[i][0] = 0;
	}

	for (int j = 0; j <= n; j++) {
		LCS[0][j] = 0;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (X[i] == Y[j]) {
				LCS[i][j] = 1 + LCS[i - 1][j - 1];
			}
			else {
				LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
			}
		}
	}

	return LCS;
}

int main() {
	// your code goes here

	array<int, m + 1> x = { 'A', 'B', 'A', 'C', 'E', 'B' };
	array<int, n + 1> y = { 'A', 'D', 'B', 'A', 'V', 'C', 'E', 'B' };

	array<array<int, n + 1>, m + 1> LCS = longest_common_subseq(x, y);

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			cout << LCS[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}